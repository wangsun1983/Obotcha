#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpContentType.hpp"

using namespace obotcha;

struct NameMap {
public:
  int id;
  const char *name;
};

#define MEMBER(X) \
{ st(HttpContentType)::Type##X,st(HttpContentType)::X->toChars()}


NameMap names[1024] = {
    MEMBER(TextHtml),
    MEMBER(TextCss),
    MEMBER(TextXml),
    MEMBER(ImageGif),
    MEMBER(ImageJpeg),
    MEMBER(ApplicationJs),
    MEMBER(ApplicationAtomXml),
    MEMBER(ApplicationRss),
    MEMBER(TextMathml),
    MEMBER(TextPlain),
    MEMBER(TextVndSunJ2meAppDes),
    MEMBER(TextVndWapWml),
    MEMBER(TextXComponent),
    MEMBER(ImagePng),
    MEMBER(ImageSvgXml),
    MEMBER(ImageTiff),
    MEMBER(ImageVndWapWbmp),
    MEMBER(ImageWebp),
    MEMBER(ImageXIcon),
    MEMBER(ImageXJng),
    MEMBER(ImageXMsBmp),
    MEMBER(ApplicationFontWoff),
    MEMBER(ApplicationJavaArchive),
    MEMBER(ApplicationJson),
    MEMBER(ApplicationMaxBinhex40),
    MEMBER(ApplicationMsword),
    MEMBER(ApplicationPdf),
    MEMBER(ApplicationPostScript),
    MEMBER(ApplicationRtf),
    MEMBER(ApplicationVndAppleMpegurl),
    MEMBER(ApplicationVndGoogleEarthKmlXml),
    MEMBER(ApplicationVndGoogleEarthKmz),
    MEMBER(ApplicationVndMsExcel),
    MEMBER(ApplicationVndMsFontObject),
    MEMBER(ApplicationVndMsPpt),
    MEMBER(ApplicationVndOasisOpendocGraphics),
    MEMBER(ApplicationVndOasisOpendocPresentation),
    MEMBER(ApplicationVndOasisOpendocSpreadsheet),
    MEMBER(ApplicationVndOasisOpendocText),
    MEMBER(ApplicationVndOpenxmlPresentation),
    MEMBER(ApplicationVndOpenXmlSheet),
    MEMBER(ApplicationVndOepnXmlDoc),
    MEMBER(ApplicationVndWapWmls),
    MEMBER(Application7z),
    MEMBER(ApplicationXCocoa),
    MEMBER(ApplicationXJavaArch),
    MEMBER(ApplicationXJavaJnlpFile),
    MEMBER(ApplicationXMakeself),
    MEMBER(ApplicationXPerl),
    MEMBER(ApplicationXPilot),
    MEMBER(ApplicationXRarCompressed),
    MEMBER(ApplicationXReadhatPkgManager),
    MEMBER(ApplicationXSea),
    MEMBER(ApplicationXShockwaveFlash),
    MEMBER(ApplicationXStuffit),
    MEMBER(ApplicationXTcl),
    MEMBER(ApplicationXX509CaCert),
    MEMBER(ApplicationXXpinstall),
    MEMBER(ApplicationXhtmlXml),
    MEMBER(ApplicationXspfXml),
    MEMBER(ApplicationZip),
    MEMBER(ApplicationOctetStream),
    MEMBER(AudioMidi),
    MEMBER(AudioMpeg),
    MEMBER(AudioOgg),
    MEMBER(AudioXM4a),
    MEMBER(AudioXRealAudio),
    MEMBER(Video3Gpp),
    MEMBER(VideoMp2t),
    MEMBER(VideoMp4),
    MEMBER(VideoMpeg),
    MEMBER(VidoQuicktime),
    MEMBER(VideoWebm),
    MEMBER(VideoXflv),
    MEMBER(VideoXM4v),
    MEMBER(VideoXMng),
    MEMBER(VideoXMsAsf),
    MEMBER(VideoXMsWmv),
    MEMBER(VideoXMsVideo),
    MEMBER(MultiPartFormData),
    MEMBER(XFormUrlEncoded),
};


void testNameIdConvert() {
  for(int i = st(HttpContentType)::TypeTextHtml;i <st(HttpContentType)::TypeMax;i++ ) {
      HttpMime mime = createHttpMime();
      mime->setTypeId(i);
      String f1 = mime->getTypeName();
      if(!f1->equals(names[i].name)) {
        printf("---[TestHttpMime name to id case1] [FAILED]--- \n");
      }

      mime->setTypeName(f1);
      if(mime->getTypeId() != i) {
        printf("---[TestHttpMime name to id case2] [FAILED]---,i is %d,id is %d \n",i,mime->getTypeId());
      }
  }

  printf("---[TestHttpMime name to id case100] [OK]--- \n");

}
