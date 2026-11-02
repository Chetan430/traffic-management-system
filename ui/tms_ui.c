/* Browser UI bridge for the original Traffic Management System C engine.
 * No automatic signal rotation or automatic vehicle processing is performed.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#ifdef _WIN32
#include <winsock2.h>
typedef SOCKET sock_t;
#define CLOSESOCK closesocket
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
typedef int sock_t;
#define CLOSESOCK close
#endif
static char outbuf[16384]; static int outlen;
static int web_printf(const char *fmt,...){ va_list a; int n; va_start(a,fmt); n=vsnprintf(outbuf+outlen,sizeof(outbuf)-(size_t)outlen,fmt,a); va_end(a); if(n>0)outlen+=n; if(outlen>(int)sizeof(outbuf)-1)outlen=sizeof(outbuf)-1; return n; }
#define printf web_printf
#define main traffic_cli_main
#include "../src/traffic.c"
#undef main
static int laneAdded[4], laneDone[4], laneEmergency[4], peak[4];
/* Only one lane may be GREEN at a time. 0=RED, 2=GREEN. */
static int laneSignal[4] = {2, 1, 1, 1};
static char resp[40000]; static int rl;
static void put(const char*s){int n=snprintf(resp+rl,sizeof(resp)-(size_t)rl,"%s",s);if(n>0)rl+=n;if(rl>(int)sizeof(resp)-1)rl=sizeof(resp)-1;}
static void putf(const char*f,...){va_list a;int n;va_start(a,f);n=vsnprintf(resp+rl,sizeof(resp)-(size_t)rl,f,a);va_end(a);if(n>0)rl+=n;if(rl>(int)sizeof(resp)-1)rl=sizeof(resp)-1;}
static void jsonstr(const char*s){put("\"");for(;*s&&rl<(int)sizeof(resp)-8;s++){if(*s=='\"'||*s=='\\'){resp[rl++]='\\';resp[rl++]=*s;}else if(*s=='\n'){resp[rl++]='\\';resp[rl++]='n';}else if(*s!='\r'&&(unsigned char)*s>=32)resp[rl++]=*s;}resp[rl]=0;put("\"");}
static void capture(void(*fn)(void)){outlen=0;outbuf[0]=0;fn();outbuf[outlen]=0;}
static int getval(const char*b,const char*k,char*out,size_t z){char p[64];const char*q;size_t i=0;snprintf(p,sizeof p,"\"%s\"",k);q=strstr(b,p);out[0]=0;if(!q)return 0;q+=strlen(p);while(*q==' '||*q==':'||*q=='\"')q++;while(*q&&*q!='\"'&&*q!=','&&*q!='}'&&i<z-1)out[i++]=*q++;out[i]=0;return 1;}
static int pint(const char*s,int*v){char*e;long n;errno=0;if(!*s)return 0;n=strtol(s,&e,10);if(e==s||errno==ERANGE||n<INT_MIN||n>INT_MAX)return 0;while(isspace((unsigned char)*e))e++;if(*e)return 0;*v=(int)n;return 1;}
static void state(void){int i;put("{\"lights\":[");for(i=0;i<4;i++){if(i)put(",");putf("\"%s\"",laneSignal[i]==2?"GREEN":"RED");}put("],\"lane\":[");for(i=0;i<4;i++){if(i)put(",");putf("{\"added\":%d,\"processed\":%d,\"em\":%d,\"peak\":%d}",laneAdded[i],laneDone[i],laneEmergency[i],peak[i]);}put("],\"queues\":");capture(displayAllLanes);jsonstr(outbuf);put(",\"density\":");capture(displayDensity);jsonstr(outbuf);put(",\"stats\":");capture(displayStatistics);jsonstr(outbuf);putf(",\"signal\":\"%s\"}",currentSignal==2?"GREEN":"RED");}
static void action(const char*path,const char*body){char a[64],b[64],c[64];int l,id,em,before;outlen=0;outbuf[0]=0;
 if(!strcmp(path,"add")){getval(body,"lane",a,sizeof a);getval(body,"id",b,sizeof b);getval(body,"emergency",c,sizeof c);if(!pint(a,&l)||l<1||l>4)printf("Invalid lane. Choose 1-4.\n");else if(!pint(b,&id))printf("Invalid input. Please enter a valid integer vehicle ID.\n");else if(id<=0)printf("Vehicle ID must be positive.\n");else{em=!strcmp(c,"true")||!strcmp(c,"1");before=totalVehiclesAdded;addVehicle(l-1,id,em);if(totalVehiclesAdded>before){laneAdded[l-1]++;if(em)laneEmergency[l-1]++;if(queueSize(l-1)>peak[l-1])peak[l-1]=queueSize(l-1);if(em){int j;for(j=0;j<4;j++)laneSignal[j]=1;laneSignal[l-1]=2;currentSignal=2;printf("\nEMERGENCY PRIORITY: Lane %d is GREEN; all other lanes are RED.\n",l);}}}}
 else if(!strcmp(path,"process")){getval(body,"lane",a,sizeof a);if(!pint(a,&l)||l<1||l>4)printf("Invalid lane. Choose 1-4.\n");else if(laneSignal[l-1]!=2){currentSignal=1;printf("Lane %d signal is not GREEN. Vehicle cannot be processed.\n",l);}else{currentSignal=2;before=totalVehiclesProcessed;processVehicle(l-1);if(totalVehiclesProcessed>before)laneDone[l-1]++;}}
 else if(!strcmp(path,"signal")){getval(body,"signal",a,sizeof a);if(!pint(a,&id)||(id!=1&&id!=2))printf("Invalid signal selection. Choose 1 (RED) or 2 (GREEN).\n");else{int j;getval(body,"lane",c,sizeof c);if(!pint(c,&l)||l<1||l>4)printf("Invalid lane. Choose 1-4.\n");else{if(id==2){for(j=0;j<4;j++)laneSignal[j]=1;laneSignal[l-1]=2;}else laneSignal[l-1]=1;currentSignal=id;printf("Lane %d signal: %s.\n",l,id==1?"RED":"GREEN");if(id==1)printf("Lane %d vehicles must wait.\n",l);else printf("Other lanes are RED; Lane %d may proceed.\n",l);}}}
 else if(!strcmp(path,"reset")){resetSimulation();memset(laneAdded,0,sizeof laneAdded);memset(laneDone,0,sizeof laneDone);memset(laneEmergency,0,sizeof laneEmergency);memset(peak,0,sizeof peak);laneSignal[0]=2;laneSignal[1]=laneSignal[2]=laneSignal[3]=1;currentSignal=2;}
}
static void sendall(sock_t s,const char*p,size_t n){while(n){int k=(int)send(s,p,(int)n,0);if(k<=0)return;p+=k;n-=(size_t)k;}}
static void reply(sock_t s,const char*type,const char*p,size_t n){char h[256];int k=snprintf(h,sizeof h,"HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %zu\r\nCache-Control: no-store\r\nAccess-Control-Allow-Origin: *\r\nConnection: close\r\n\r\n",type,n);sendall(s,h,(size_t)k);sendall(s,p,n);}
static void serveindex(sock_t s){const char*paths[]={"ui/index.html","index.html"};int i;for(i=0;i<2;i++){FILE*f=fopen(paths[i],"rb");if(f){long n;char*p;fseek(f,0,SEEK_END);n=ftell(f);rewind(f);p=malloc((size_t)n+1);if(p&&fread(p,1,(size_t)n,f)==(size_t)n)reply(s,"text/html; charset=utf-8",p,(size_t)n);free(p);fclose(f);return;}}reply(s,"text/plain","ui/index.html not found; run server from project root",53);}
static void handle(sock_t s){char req[8192],method[8],path[128],*body;int n,total=0;while(total<(int)sizeof(req)-1&&(n=(int)recv(s,req+total,(int)sizeof(req)-1-total,0))>0){total+=n;req[total]=0;body=strstr(req,"\r\n\r\n");if(body){char*cl=strstr(req,"Content-Length:");int need=cl?atoi(cl+15):0;if(total-(int)(body+4-req)>=need)break;}}if(!total)return;req[total]=0;sscanf(req,"%7s %127s",method,path);body=strstr(req,"\r\n\r\n");body=body?body+4:req+total;if(!strcmp(method,"GET")&&!strcmp(path,"/")){serveindex(s);return;}rl=0;resp[0]=0;if(!strcmp(method,"GET")&&!strcmp(path,"/api/state")){state();}else if(!strcmp(method,"POST")&&(!strncmp(path,"/api/",5))){action(path+5,body);put("{\"ok\":");put((strstr(outbuf,"Invalid")||strstr(outbuf,"not GREEN")||strstr(outbuf,"full.")||strstr(outbuf,"empty.")||strstr(outbuf,"positive"))?"false":"true");put(",\"message\":");jsonstr(outbuf);put(",\"state\":");state();put("}");}else{reply(s,"application/json","{\"error\":\"not found\"}",21);return;}reply(s,"application/json",resp,(size_t)rl);}
int main(int argc,char**argv){int port=argc>1?atoi(argv[1]):8080;struct sockaddr_in a;sock_t srv,c;int yes=1;
#ifdef _WIN32
WSADATA w;WSAStartup(MAKEWORD(2,2),&w);
#endif
initializeQueues();laneSignal[0]=2;laneSignal[1]=laneSignal[2]=laneSignal[3]=1;currentSignal=2;srv=socket(AF_INET,SOCK_STREAM,0);setsockopt(srv,SOL_SOCKET,SO_REUSEADDR,(const char*)&yes,sizeof yes);memset(&a,0,sizeof a);a.sin_family=AF_INET;a.sin_addr.s_addr=inet_addr("127.0.0.1");a.sin_port=htons((unsigned short)port);if(bind(srv,(struct sockaddr*)&a,sizeof a)!=0||listen(srv,12)!=0){fprintf(stderr,"Cannot listen on port %d\n",port);return 1;}printf("Traffic Management System UI: http://127.0.0.1:%d\n",port);for(;;){c=accept(srv,NULL,NULL);if(c!=(sock_t)-1){handle(c);CLOSESOCK(c);}}}
