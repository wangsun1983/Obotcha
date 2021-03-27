#ifndef __OBOTCHA_HTTP_CONTENT_TYPE_HPP__
#define __OBOTCHA_HTTP_CONTENT_TYPE_HPP__

//according nginx/conf/mime.types

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "HttpCookie.hpp"
#include "Mutex.hpp"
#include "File.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpContentType) {

public:
    enum Type {
        TypeTextHtml = 0,
        TypeTextCss,
        TypeTextXml,
        TypeImageGif,
        TypeImageJpeg,
        TypeApplicationJs,
        TypeApplicationAtomXml,
        TypeApplicationRss,
        TypeMathml,
        TypeTextPlain,
        TypeTextVndSunJ2meAppDes,
        TypeVndWapWml,
        TypeXComponent,
        TypeImagePng,
        TypeImageSvgXml,
        TypeImageTiff,
        TypeImageVndWapWbmp,
        TypeImageWebp,
        TypeImageXIcon,
        TypeImageXJng,
        TypeImageXMsBmp,
        TypeApplicationFontWoff,
        TypeApplicationJavaArchive,
        TypeApplicationJson,
        TypeApplicationMaxBinhex40,
        TypeApplicationMsword,
        TypeApplicationPdf,
        TypeApplicationPostScript,
        TypeApplicationRtf,
        TypeApplicationVndAppleMpegurl,
        TypeApplicationVndGoogleEarthKmlXml,
        TypeApplicationVndGoogleEarthKmz,
        TypeApplicationVndMsExcel,
        TypeApplicationVndMsFontObject,
        TypeApplicationVndMsPpt,
        TypeApplicationVndOasisOpendocGraphics,
        TypeApplicationVndOasisOpendocPresentation,
        TypeApplicationVndOasisOpendocSpreadsheet,
        TypeApplicationVndOasisOpendocText,
        TypeApplicationVndOpenxmlPresentation,
        TypeApplicationVndOpenXmlSheet,
        TypeApplicationVndOepnXmlDoc,
        TypeApplicationVndWapWmls,
        TypeApplication7z,
        TypeApplicationXCocoa,
        TypeApplicationXJavaArch,
        TypeApplicationXJavaJnlpFile,
        TypeApplicationXMakeself,
        TypeApplicationXPerl,
        TypeApplicationXPilot,
        TypeApplicationXRarCompressed,
        TypeApplicationXReadhatPkgManager,
        TypeApplicationXSea,
        TypeApplicationXShockwaveFlash,
        TypeApplicationXStuffit,
        TypeApplicationXTcl,
        TypeApplicationXX509CaCert,
        TypeApplicationXXpinstall,
        TypeApplicationXhtmXml,
        TypeApplicationXspfXml,
        TypeApplicationZip,
        TypeApplicationOctetStream,
        TypeSuffixMsi,
        TypeAudioMidi,
        TypeAudioMpeg,
        TypeAudioOgg,
        TypeAudioXM4a,
        TypeAudioXRealAudio,
        TypeVideo3Gpp,
        TypeVideoMp2t,
        TypeVideoMp4,
        TypeVideoMpeg,
        TypeVidoQuicktime,
        TypeVideoWebm,
        TypeVideoXflv,
        TypeVideoXM4v,
        TypeVideoXMng,
        TypeVideoXMsAsf,
        TypeVideoXMsWmv,
        TypeVideoXMsVideo,
        TypeMultiPartFormData,
        TypeXFormUrlEncoded
    };
    //static ArrayList<String> getSupportFileSuffix(String);
    //static String getContentType(String suffix);

    //text/html(html htm shtml)
    const static String TextHtml;//text/html(html htm shtml)
    const static String SuffixHtml;
    const static String SuffixHtm;
    const static String SuffixShtml;

    
    //text/css(css)
    const static String TextCss;
    const static String SuffixCss;

    //text/xml(xml)
    const static String TextXml;
    const static String SuffixXml;

    //image/gif(gif)
    const static String ImageGif;
    const static String SuffixGif;

    //image/jpeg(jpeg jpg)
    const static String ImageJpeg;
    const static String SuffixJpeg;
    const static String SuffixJpg;

    //application/javascript(js)
    const static String ApplicationJs;
    const static String SuffixJs;

    //application/atom+xml(atom)
    const static String ApplicationAtomXml;
    const static String SuffixAtom;

    //application/rss+xml(rss)
    const static String ApplicationRss;
    const static String SuffixRss;

    //text/mathml(mml)
    const static String TextMathml;
    const static String SuffixMml;

    //text/plain(txt)
    const static String TextPlain;
    const static String SuffixTxt;

    //text/vnd.sun.j2me.app-descriptor(jad)
    const static String TextVndSunJ2meAppDes;
    const static String SuffixJad;

    //text/vnd.wap.wml                                 wml;
    const static String TextVndWapWml;
    const static String SuffixWml;

    //text/x-component                                 htc;
    const static String TextXComponent;
    const static String SuffixHtc;

    //image/png                                        png;
    const static String ImagePng;
    const static String SuffixPng;

    //image/svg+xml                                    svg svgz;
    const static String ImageSvgXml;
    const static String SuffixSvg;
    const static String SuffixSvgz;

    //image/tiff                                       tif tiff;
    const static String ImageTiff;
    const static String SuffixTif;
    const static String SuffixTiff;
    
    //image/vnd.wap.wbmp                               wbmp;
    const static String ImageVndWapWbmp;
    const static String SuffixWbmp;

    //image/webp                                       webp;
    const static String ImageWebp;
    const static String SuffixWebp;

    //image/x-icon                                     ico;
    const static String ImageXIcon;
    const static String SuffixIco;

    //image/x-jng                                      jng;
    const static String ImageXJng;
    const static String SuffixJng;

    //image/x-ms-bmp                                   bmp;
    const static String ImageXMsBmp;
    const static String SuffixBmp;

    //application/font-woff                            woff;
    const static String ApplicationFontWoff;
    const static String SuffixWoff;

    //application/java-archive                         jar war ear;
    const static String ApplicationJavaArchive;
    const static String SuffixJar;
    const static String SuffixWar;
    const static String SuffixEar;

    //application/json                                 json;
    const static String ApplicationJson;
    const static String SuffixJson;

    //application/mac-binhex40                         hqx;
    const static String ApplicationMaxBinhex40;
    const static String SuffixHqx;

    //application/msword                               doc;
    const static String ApplicationMsword;
    const static String SuffixDoc;

    //application/pdf                                  pdf;
    const static String ApplicationPdf;
    const static String SuffixPdf;

    //application/postscript                           ps eps ai;
    const static String ApplicationPostScript;
    const static String SuffixPs;
    const static String SuffixEps;
    const static String SuffixAi;

    //application/rtf                                  rtf;
    const static String ApplicationRtf;
    const static String SuffixRtf;

    //application/vnd.apple.mpegurl                    m3u8;
    const static String ApplicationVndAppleMpegurl;
    const static String SuffixM3u8;

    //application/vnd.google-earth.kml+xml             kml;
    const static String ApplicationVndGoogleEarthKmlXml;
    const static String SuffixKml;

    //application/vnd.google-earth.kmz                 kmz;
    const static String ApplicationVndGoogleEarthKmz;
    const static String SuffixKmz;

    //application/vnd.ms-excel                         xls;
    const static String ApplicationVndMsExcel;
    const static String SuffixXls;

    //application/vnd.ms-fontobject                    eot;
    const static String ApplicationVndMsFontObject;
    const static String SuffixEot;

    //application/vnd.ms-powerpoint                    ppt;
    const static String ApplicationVndMsPpt;
    const static String SuffixPpt;

    //application/vnd.oasis.opendocument.graphics      odg;
    const static String ApplicationVndOasisOpendocGraphics;
    const static String SuffixOdj;

    //application/vnd.oasis.opendocument.presentation  odp;
    const static String ApplicationVndOasisOpendocPresentation;
    const static String SuffixOdp;

    //application/vnd.oasis.opendocument.spreadsheet   ods;
    const static String ApplicationVndOasisOpendocSpreadsheet;
    const static String SuffixOds;

    //application/vnd.oasis.opendocument.text          odt;
    const static String ApplicationVndOasisOpendocText;
    const static String SuffixOdt;

    //application/vnd.openxmlformats-officedocument.presentationml.presentation
                                                     //pptx;
    const static String ApplicationVndOpenxmlPresentation;
    const static String SuffixPptx;

    //application/vnd.openxmlformats-officedocument.spreadsheetml.sheet
    //                                                 xlsx;
    const static String ApplicationVndOpenXmlSheet;
    const static String SuffixXlsx;

    //application/vnd.openxmlformats-officedocument.wordprocessingml.document
    //                                                 docx;
    const static String ApplicationVndOepnXmlDoc;
    const static String SuffixDocx;

    //application/vnd.wap.wmlc                         wmlc;
    const static String ApplicationVndWapWmls;
    const static String SuffixWmlc;

    //application/x-7z-compressed                      7z;
    const static String Application7z;
    const static String Suffix7z;

    //application/x-cocoa                              cco;
    const static String ApplicationXCocoa;
    const static String SuffixCco;

    //application/x-java-archive-diff                  jardiff;
    const static String ApplicationXJavaArch;
    const static String SuffixJardiff;

    //application/x-java-jnlp-file                     jnlp;
    const static String ApplicationXJavaJnlpFile;
    const static String SuffixJnlp;

    //application/x-makeself                           run;
    const static String ApplicationXMakeself;
    const static String SuffixRun;

    //application/x-perl                               pl pm;
    const static String ApplicationXPerl;
    const static String SuffixPl;
    const static String SuffixPm;

    //application/x-pilot                              prc pdb;
    const static String ApplicationXPilot;
    const static String SuffixPrc;
    const static String SuffixPdb;

    //application/x-rar-compressed                     rar;
    const static String ApplicationXRarCompressed;
    const static String SuffixRar;

    //application/x-redhat-package-manager             rpm;
    const static String ApplicationXReadhatPkgManager;
    const static String SuffixRpm;

    //application/x-sea                                sea;
    const static String ApplicationXSea;
    const static String SuffixSea;

    //application/x-shockwave-flash                    swf;
    const static String ApplicationXShockwaveFlash;
    const static String SuffixSwf;

    //application/x-stuffit                            sit;
    const static String ApplicationXStuffit;
    const static String SuffixSit;

    //application/x-tcl                                tcl tk;
    const static String ApplicationXTcl;
    const static String SuffixTcl;
    const static String SuffixTk;

    //application/x-x509-ca-cert                       der pem crt;
    const static String ApplicationXX509CaCert;
    const static String SuffixDer;
    const static String SuffixPem;
    const static String SuffixCrt;
    
    //application/x-xpinstall                          xpi;
    const static String ApplicationXXpinstall;
    const static String SuffixXpi;

    //application/xhtml+xml                            xhtml;
    const static String ApplicationXhtmlXml;
    const static String SuffixXhtml;

    //application/xspf+xml                             xspf;
    const static String ApplicationXspfXml;
    const static String SuffixXspf;

    //application/zip                                  zip;
    const static String ApplicationZip;
    const static String SuffixZip;

    //application/octet-stream                         bin exe dll;
    const static String ApplicationOctetStream;
    const static String SuffixBin;
    const static String SuffixExe;
    const static String SuffixDll;
    
    //application/octet-stream                         deb;
    const static String SuffixDeb;

    //application/octet-stream                         dmg;
    const static String SuffixDmg;

    //application/octet-stream                         iso img;
    const static String SuffixIso;
    const static String SuffixImg;

    //application/octet-stream                         msi msp msm;
    const static String SuffixMsi;
    const static String SuffixMsp;
    const static String SuffixMsm;

    //audio/midi                                       mid midi kar;
    const static String AudioMidi;
    const static String SuffixMid;
    const static String SuffixMidi;
    const static String SuffixKar;

    //audio/mpeg                                       mp3;
    const static String AudioMpeg;
    const static String SuffixMp3;

    //audio/ogg                                        ogg;
    const static String AudioOgg;
    const static String SuffixOgg;

    //audio/x-m4a                                      m4a;
    const static String AudioXM4a;
    const static String SuffixM4a;

    //audio/x-realaudio                                ra;
    const static String AudioXRealAudio;
    const static String SuffixRa;

    //video/3gpp                                       3gpp 3gp;
    const static String Video3Gpp;
    const static String Suffix3Gpp;
    const static String Sufix3Gp;

    //video/mp2t                                       ts;
    const static String VideoMp2t;
    const static String SuffixTs;

    //video/mp4                                        mp4;
    const static String VideoMp4;
    const static String SuffixMp4;

    //video/mpeg                                       mpeg mpg;
    const static String VideoMpeg;
    const static String SuffixMpeg;
    const static String SuffixMpg;

    //video/quicktime                                  mov;
    const static String VidoQuicktime;
    const static String SuffixMov;

    //video/webm                                       webm;
    const static String VideoWebm;
    const static String SuffixWebm;

    //video/x-flv                                      flv;
    const static String VideoXflv;
    const static String SuffixFlv;

    //video/x-m4v                                      m4v;
    const static String VideoXM4v;
    const static String SuffixM4V;

    //video/x-mng                                      mng;
    const static String VideoXMng;
    const static String SuffixMng;

    //video/x-ms-asf                                   asx asf;
    const static String VideoXMsAsf;
    const static String SuffixAsx;
    const static String SuffixAsf;

    //video/x-ms-wmv                                   wmv;
    const static String VideoXMsWmv;
    const static String SuffixWmv;

    //video/x-msvideo                                  avi;
    const static String VideoXMsVideo;
    const static String SuffixAvi;

    //multipart/form-data 
    const static String MultiPartFormData;
    const static String FormData;
    const static String Boundary;

    //application/x-www-form-urlencoded
    const static String XFormUrlEncoded;

    //charset
    const static String CharSet;

    _HttpContentType();
    _HttpContentType(String);

    void import(String value);

    String toString();

    void setType(String);
    void setCharSet(String);
    void setBoundary(String);

    String getType();
    String getCharSet();
    String getBoundary();


private:
    String mContentType;
    String mSubtype;
    String mSubValue;
    String mCharset;

};

}
#endif
