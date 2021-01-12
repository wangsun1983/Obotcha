
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TcpClient.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "HttpUrlParser.hpp"
#include "HttpClient.hpp"
#include "HttpUrl.hpp"
#include "HttpPacket.hpp"
#include "HttpMethod.hpp"
#include "HttpRequest.hpp"

using namespace obotcha;

//no data
#if 0
GET /login HTTP/1.1
Content-Type: multipart/form-data
User-Agent: PostmanRuntime/7.22.0
Accept: */*
Cache-Control: no-cache
Postman-Token: 5de7d9b5-9ac2-418f-ad0e-7051e483a2fe
Host: 192.168.1.10:8012
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
#endif

//form-data
#if 0
GET /login HTTP/1.1
Content-Type: multipart/form-data; boundary=--------------------------791004031292697662337055
User-Agent: PostmanRuntime/7.22.0
Accept: */*
Cache-Control: no-cache
Postman-Token: 0ea69276-4d99-4868-aa2d-2b46bd4b49ae
Host: 192.168.1.10:8012
Accept-Encoding: gzip, deflate, br
Content-Length: 270
Connection: keep-alive

----------------------------791004031292697662337055
Content-Disposition: form-data; name="key1"

val1
----------------------------791004031292697662337055
Content-Disposition: form-data; name="key2"

val2
----------------------------791004031292697662337055--
#endif

//x-www-form-urlend
#if 0
GET /login HTTP/1.1
Content-Type: application/x-www-form-urlencoded
User-Agent: PostmanRuntime/7.22.0
Accept: */*
Cache-Control: no-cache
Postman-Token: fbb6dd6c-8d4a-4258-9b60-951010ca38ae
Host: 192.168.1.10:8012
Accept-Encoding: gzip, deflate, br
Content-Length: 19
Connection: keep-alive

key1=val1&key2=val2
#endif

//raw
#if 0
GET /login HTTP/1.1
Content-Type: application/x-www-form-urlencoded
User-Agent: PostmanRuntime/7.22.0
Accept: */*
Cache-Control: no-cache
Postman-Token: 17bded6c-840a-4706-ac73-9100f8dd6940
Host: 192.168.1.10:8012
Accept-Encoding: gzip, deflate, br
Content-Length: 10
Connection: keep-alive

fffffsssss
#endif

//binary
#if 0
GET /login HTTP/1.1
Content-Type: application/x-www-form-urlencoded
User-Agent: PostmanRuntime/7.22.0
Accept: */*
Cache-Control: no-cache
Postman-Token: e6f8eb81-bc3b-4fbe-8cc3-69b37e4f8843
Host: 192.168.1.10:8012
Accept-Encoding: gzip, deflate, br
Content-Length: 671
Connection: keep-alive

PK...........N............
. .writep.cppUT
...r.\.V._.r.\ux.............mS.n.0....#z1.M.K.[Z)j.j...HV=T.B0$..6....M.}.8.&..`.<...
\pY...!..X.....z. ...W...j....`.....<bU!...2(.z.4....Z.\...!=..@S......T......E.4Y. ..H3u..Q..-...$. (...C7,.(^G.7......dQ...]..H..4.Y...u:.*..(D.j.....9K./)...Og.u...x..,n
.....t...A.W.H-.!.....h".>y...Q.....P.M....J..P.|..`0.o.....V......e.;6i...p5...!...Y..._...AU.>..{.6.KZ..j?.k.......=....C..2}^g...bm...qMY/&.l.0Ig.....!.b...tb@....I...O.#.............Q..c..*..oa.l...d.UH  ..a..K..rj...... ..=......6........PK..<..!........PK.............N<..!........
. ...............writep.cppUT
...r.\.V._.r.\ux.............PK..........X...1.....
#endif

int main() {

    String urlstr = "http://192.168.1.10:8012/log.zip";
    HttpUrl url = st(HttpUrlParser)::parseUrl(urlstr);
    
    HttpRequest request = createHttpRequest(st(HttpMethod)::Get,url);

    //while(1) {
    HttpClient client = createHttpClient();
    client->execute(request);
    //printf("result is %s \n",result->toChars());
    //}
    while(1){}
/*    
    String request =  "http://su:abc@localhost/test.cgi?a=b&c=d";
    HttpUrlParser parser = createHttpUrlParser();
    parser->parseUrl(request);
    //parser->parseQuery("q=search&p=123");
    request =  "http://abdd@localhost/test.cgi?a=b&c=d";
    //HttpUrlParser parser = createHttpUrlParser();
    parser->parseUrl(request);
    //while(1) {}
*/    

}
