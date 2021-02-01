#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpContentType.hpp"
#include "AutoLock.hpp"
#include "HttpHeaderParser.hpp"

namespace obotcha {

//text/html(html htm shtml)
const int _HttpContentType::TypeTextHtml = 0;
const String _HttpContentType::TextHtml = createString("text/html");//text/html(html htm shtml)
const String _HttpContentType::SuffixHtml = createString("html");
const String _HttpContentType::SuffixHtm = createString("htm");
const String _HttpContentType::SuffixShtml = createString("shtml");

//text/css(css)
const int _HttpContentType::TypeTextCss = 1;
const String _HttpContentType::TextCss = createString("text/css");
const String _HttpContentType::SuffixCss = createString("css");

//text/xml(xml)
const int _HttpContentType::TypeTextXml = 2;
const String _HttpContentType::TextXml = createString("text/xml");
const String _HttpContentType::SuffixXml= createString("xml");

//image/gif(gif)
const int _HttpContentType::TypeImageGif = 3;
const String _HttpContentType::ImageGif = createString("image/gif");
const String _HttpContentType::SuffixGif = createString("gif");

//image/jpeg(jpeg jpg)
const int _HttpContentType::TypeImageJpeg = 4;
const String _HttpContentType::ImageJpeg = createString("image/jpeg");
const String _HttpContentType::SuffixJpeg = createString("jpeg");
const String _HttpContentType::SuffixJpg = createString("jpg");

//application/javascript(js)
const int _HttpContentType::TypeApplicationJs = 5;
const String _HttpContentType::ApplicationJs = createString("application/javascript");
const String _HttpContentType::SuffixJs = createString("js");

//application/atom+xml(atom)
const int _HttpContentType::TypeApplicationAtomXml = 6;
const String _HttpContentType::ApplicationAtomXml = createString("application/atom+xml");
const String _HttpContentType::SuffixAtom = createString("atom");

//application/rss+xml(rss)
const int _HttpContentType::TypeApplicationRss = 7;
const String _HttpContentType::ApplicationRss = createString("application/rss+xml");
const String _HttpContentType::SuffixRss = createString("rss");

//text/mathml(mml)
const int _HttpContentType::TypeMathml = 8;
const String _HttpContentType::TextMathml = createString("text/mathml");
const String _HttpContentType::SuffixMml = createString("mml");

//text/plain(txt)
const int _HttpContentType::TypeTextPlain = 9;
const String _HttpContentType::TextPlain = createString("text/plain");
const String _HttpContentType::SuffixTxt = createString("txt");

//text/vnd.sun.j2me.app-descriptor(jad)
const int _HttpContentType::TypeTextVndSunJ2meAppDes = 10;
const String _HttpContentType::TextVndSunJ2meAppDes = createString("text/vnd.sun.j2me.app-descriptor");
const String _HttpContentType::SuffixJad = createString("jar");

//text/vnd.wap.wml                                 wml;
const int _HttpContentType::TypeVndWapWml = 11;
const String _HttpContentType::TextVndWapWml = createString("text/vnd.wap.wml");    
const String _HttpContentType::SuffixWml = createString("wml");    

//text/x-component                                 htc;
const int _HttpContentType::TypeXComponent = 12;
const String _HttpContentType::TextXComponent = createString("text/x-component");  
const String _HttpContentType::SuffixHtc = createString("htc");    

//image/png      png;
const int _HttpContentType::TypeImagePng = 13;
const String _HttpContentType::ImagePng = createString("image/png");    
const String _HttpContentType::SuffixPng = createString("png");    

//image/svg+xml     svg svgz;
const int _HttpContentType::TypeImageSvgXml = 14;
const String _HttpContentType::ImageSvgXml = createString("image/svg+xml");    
const String _HttpContentType::SuffixSvg = createString("svg");    
const String _HttpContentType::SuffixSvgz = createString("svgz");    

//image/tiff     tif tiff;
const int _HttpContentType::TypeImageTiff = 15;
const String _HttpContentType::ImageTiff = createString("image/tiff");    
const String _HttpContentType::SuffixTif = createString("tif");    
const String _HttpContentType::SuffixTiff = createString("tiff");    
    
//image/vnd.wap.wbmp                               wbmp;
const int _HttpContentType::TypeImageVndWapWbmp = 16;
const String _HttpContentType::ImageVndWapWbmp = createString("image/vnd.wap.wbmp");    
const String _HttpContentType::SuffixWbmp = createString("wbmp");    

//image/webp     webp;
const int _HttpContentType::TypeImageWebp = 17;
const String _HttpContentType::ImageWebp = createString("image/webp");    
const String _HttpContentType::SuffixWebp = createString("webp");    

//image/x-icon      ico;
const int _HttpContentType::TypeImageXIcon = 18;
const String _HttpContentType::ImageXIcon = createString("image/x-icon");    
const String _HttpContentType::SuffixIco = createString("ico");    

//image/x-jng    jng;
const int _HttpContentType::TypeImageXJng = 19;
const String _HttpContentType::ImageXJng = createString("image/x-jng");    
const String _HttpContentType::SuffixJng = createString("jng");    

//image/x-ms-bmp    bmp;
const int _HttpContentType::TypeImageXMsBmp = 20;
const String _HttpContentType::ImageXMsBmp = createString("image/x-ms-bmp");    
const String _HttpContentType::SuffixBmp = createString("bmp");    

//application/font-woff                            woff;
const int _HttpContentType::TypeApplicationFontWoff = 21;
const String _HttpContentType::ApplicationFontWoff = createString("application/font-woff");    
const String _HttpContentType::SuffixWoff = createString("woff");    

//application/java-archive                         jar war ear;
const int _HttpContentType::TypeApplicationJavaArchive = 22;
const String _HttpContentType::ApplicationJavaArchive = createString("application/java-archive");    
const String _HttpContentType::SuffixJar = createString("jar");    
const String _HttpContentType::SuffixWar = createString("war");    
const String _HttpContentType::SuffixEar = createString("ear");    

//application/json                                 json;
const int _HttpContentType::TypeApplicationJson = 23;
const String _HttpContentType::ApplicationJson = createString("application/json");    
const String _HttpContentType::SuffixJson = createString("json");    

//application/mac-binhex40                         hqx;
const int _HttpContentType::TypeApplicationMaxBinhex40 = 24;
const String _HttpContentType::ApplicationMaxBinhex40 = createString("application/mac-binhex40");    
const String _HttpContentType::SuffixHqx = createString("hqx");    

//application/msword                               doc;
const int _HttpContentType::TypeApplicationMsword = 25;
const String _HttpContentType::ApplicationMsword = createString("application/msword");    
const String _HttpContentType::SuffixDoc = createString("doc");    

//application/pdf                                  pdf;
const int _HttpContentType::TypeApplicationPdf = 26;
const String _HttpContentType::ApplicationPdf = createString("application/pdf");    
const String _HttpContentType::SuffixPdf = createString("pdf");    

//application/postscript                           ps eps ai;
const int _HttpContentType::TypeApplicationPostScript = 27;
const String _HttpContentType::ApplicationPostScript = createString("application/postscript");    
const String _HttpContentType::SuffixPs = createString("ps");
const String _HttpContentType::SuffixEps = createString("eps");
const String _HttpContentType::SuffixAi = createString("ai");

//application/rtf                                  rtf;
const int _HttpContentType::TypeApplicationRtf = 28;
const String _HttpContentType::ApplicationRtf = createString("application/rtf");    
const String _HttpContentType::SuffixRtf = createString("rtf");    

//application/vnd.apple.mpegurl                    m3u8;
const int _HttpContentType::TypeApplicationVndAppleMpegurl = 29;
const String _HttpContentType::ApplicationVndAppleMpegurl = createString("application/vnd.apple.mpegurl");    
const String _HttpContentType::SuffixM3u8 = createString("m3u8");    

//application/vnd.google-earth.kml+xml             kml;
const int _HttpContentType::TypeApplicationVndGoogleEarthKmlXml = 30;
const String _HttpContentType::ApplicationVndGoogleEarthKmlXml = createString("application/vnd.google-earth.kml+xml");    
const String _HttpContentType::SuffixKml = createString("kml");    

//application/vnd.google-earth.kmz                 kmz;
const int _HttpContentType::TypeApplicationVndGoogleEarthKmz = 31;
const String _HttpContentType::ApplicationVndGoogleEarthKmz = createString("application/vnd.google-earth.kmz");    
const String _HttpContentType::SuffixKmz = createString("kmz");    

//application/vnd.ms-excel                         xls;
const int _HttpContentType::TypeApplicationVndMsExcel = 32;
const String _HttpContentType::ApplicationVndMsExcel = createString("application/vnd.ms-excel");    
const String _HttpContentType::SuffixXls = createString("xls");    

//application/vnd.ms-fontobject                    eot;
const int _HttpContentType::TypeApplicationVndMsFontObject = 33;
const String _HttpContentType::ApplicationVndMsFontObject = createString("application/vnd.ms-fontobject");    
const String _HttpContentType::SuffixEot = createString("eot");    

//application/vnd.ms-powerpoint                    ppt;
const int _HttpContentType::TypeApplicationVndMsPpt = 34;
const String _HttpContentType::ApplicationVndMsPpt = createString("application/vnd.ms-powerpoint");    
const String _HttpContentType::SuffixPpt = createString("ppt");    

//application/vnd.oasis.opendocument.graphics      odg;
const int _HttpContentType::TypeApplicationVndOasisOpendocGraphics = 35;
const String _HttpContentType::ApplicationVndOasisOpendocGraphics = createString("application/vnd.oasis.opendocument.graphics");    
const String _HttpContentType::SuffixOdj = createString("odg");    

//application/vnd.oasis.opendocument.presentation  odp;
const int _HttpContentType::TypeApplicationVndOasisOpendocPresentation = 36;
const String _HttpContentType::ApplicationVndOasisOpendocPresentation = createString("application/vnd.oasis.opendocument.presentation");    
const String _HttpContentType::SuffixOdp = createString("odp");    

//application/vnd.oasis.opendocument.spreadsheet   ods;
const int _HttpContentType::TypeApplicationVndOasisOpendocSpreadsheet = 37;
const String _HttpContentType::ApplicationVndOasisOpendocSpreadsheet = createString("application/vnd.oasis.opendocument.spreadsheet");    
const String _HttpContentType::SuffixOds = createString("ods");    

//application/vnd.oasis.opendocument.text          odt;
const int _HttpContentType::TypeApplicationVndOasisOpendocText = 38;
const String _HttpContentType::ApplicationVndOasisOpendocText = createString("application/vnd.oasis.opendocument.text");    
const String _HttpContentType::SuffixOdt = createString("odt");    

//application/vnd.openxmlformats-officedocument.presentationml.presentation
               //pptx;
const int _HttpContentType::TypeApplicationVndOpenxmlPresentation = 39;
const String _HttpContentType::ApplicationVndOpenxmlPresentation = createString("application/vnd.openxmlformats-officedocument.presentationml.presentation");    
const String _HttpContentType::SuffixPptx = createString("pptx");    

//application/vnd.openxmlformats-officedocument.spreadsheetml.sheet
//               xlsx;
const int _HttpContentType::TypeApplicationVndOpenXmlSheet = 40;
const String _HttpContentType::ApplicationVndOpenXmlSheet = createString("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");    
const String _HttpContentType::SuffixXlsx = createString("xlsx");    

//application/vnd.openxmlformats-officedocument.wordprocessingml.document
//               docx;
const int _HttpContentType::TypeApplicationVndOepnXmlDoc = 41;
const String _HttpContentType::ApplicationVndOepnXmlDoc = createString("application/vnd.openxmlformats-officedocument.wordprocessingml.document");    
const String _HttpContentType::SuffixDocx = createString("docx");    

//application/vnd.wap.wmlc                         wmlc;
const int _HttpContentType::TypeApplicationVndWapWmls = 42;
const String _HttpContentType::ApplicationVndWapWmls = createString("application/vnd.wap.wmlc");    
const String _HttpContentType::SuffixWmlc = createString("wmlc");    

//application/x-7z-compressed                      7z;
const int _HttpContentType::TypeApplication7z = 43;
const String _HttpContentType::Application7z = createString("application/x-7z-compressed");    
const String _HttpContentType::Suffix7z = createString("7z");    

//application/x-cocoa                              cco;
const int _HttpContentType::TypeApplicationXCocoa = 44;
const String _HttpContentType::ApplicationXCocoa = createString("application/x-cocoa");    
const String _HttpContentType::SuffixCco = createString("cco");    

//application/x-java-archive-diff                  jardiff;
const int _HttpContentType::TypeApplicationXJavaArch = 45;
const String _HttpContentType::ApplicationXJavaArch = createString("application/x-java-archive-diff");    
const String _HttpContentType::SuffixJardiff = createString("jardiff");    

//application/x-java-jnlp-file                     jnlp;
const int _HttpContentType::TypeApplicationXJavaJnlpFile = 46;
const String _HttpContentType::ApplicationXJavaJnlpFile = createString("application/x-java-jnlp-file");    
const String _HttpContentType::SuffixJnlp = createString("jnlp");    

//application/x-makeself                           run;
const int _HttpContentType::TypeApplicationXMakeself = 47;
const String _HttpContentType::ApplicationXMakeself = createString("application/x-makeself");    
const String _HttpContentType::SuffixRun = createString("run");    

//application/x-perl                               pl pm;
const int _HttpContentType::TypeApplicationXPerl = 48;
const String _HttpContentType::ApplicationXPerl = createString("application/x-perl");    
const String _HttpContentType::SuffixPl = createString("pl");    
const String _HttpContentType::SuffixPm = createString("pm");    

//application/x-pilot                              prc pdb;
const int _HttpContentType::TypeApplicationXPilot = 49;
const String _HttpContentType::ApplicationXPilot = createString("application/x-pilot");    
const String _HttpContentType::SuffixPrc = createString("prc");    
const String _HttpContentType::SuffixPdb = createString("pdb");    

//application/x-rar-compressed                     rar;
const int _HttpContentType::TypeApplicationXRarCompressed = 50;
const String _HttpContentType::ApplicationXRarCompressed = createString("application/x-rar-compressed");    
const String _HttpContentType::SuffixRar = createString("rar");    

//application/x-redhat-package-manager             rpm;
const int _HttpContentType::TypeApplicationXReadhatPkgManager = 51;
const String _HttpContentType::ApplicationXReadhatPkgManager = createString("application/x-redhat-package-manager");    
const String _HttpContentType::SuffixRpm = createString("rpm");    

//application/x-sea                                sea;
const int _HttpContentType::TypeApplicationXSea = 52;
const String _HttpContentType::ApplicationXSea = createString("application/x-sea");    
const String _HttpContentType::SuffixSea = createString("sea");    

//application/x-shockwave-flash                    swf;
const int _HttpContentType::TypeApplicationXShockwaveFlash = 53;
const String _HttpContentType::ApplicationXShockwaveFlash = createString("application/x-shockwave-flash");    
const String _HttpContentType::SuffixSwf = createString("swf");    

//application/x-stuffit                            sit;
const int _HttpContentType::TypeApplicationXStuffit = 54;
const String _HttpContentType::ApplicationXStuffit = createString("application/x-stuffit");    
const String _HttpContentType::SuffixSit = createString("sit");    

//application/x-tcl                                tcl tk;
const int _HttpContentType::TypeApplicationXTcl = 55;
const String _HttpContentType::ApplicationXTcl = createString("application/x-tcl");    
const String _HttpContentType::SuffixTcl = createString("tcl");    
const String _HttpContentType::SuffixTk = createString("tk");    

//application/x-x509-ca-cert                       der pem crt;
const int _HttpContentType::TypeApplicationXX509CaCert = 56;
const String _HttpContentType::ApplicationXX509CaCert = createString("application/x-x509-ca-cert");    
const String _HttpContentType::SuffixDer = createString("der");    
const String _HttpContentType::SuffixPem = createString("pem");    
const String _HttpContentType::SuffixCrt = createString("crt");    
    
//application/x-xpinstall                          xpi;
const int _HttpContentType::TypeApplicationXXpinstall = 57;
const String _HttpContentType::ApplicationXXpinstall = createString("application/x-xpinstall");    
const String _HttpContentType::SuffixXpi = createString("xpi");    

//application/xhtml+xml                            xhtml;
const int _HttpContentType::TypeApplicationXhtmXml = 58;
const String _HttpContentType::ApplicationXhtmlXml = createString("application/xhtml+xml");    
const String _HttpContentType::SuffixXhtml = createString("xhtml");    

//application/xspf+xml                             xspf;
const int _HttpContentType::TypeApplicationXspfXml = 59;
const String _HttpContentType::ApplicationXspfXml = createString("application/xspf+xml");    
const String _HttpContentType::SuffixXspf = createString("xspf");    

//application/zip                                  zip;
const int _HttpContentType::TypeApplicationZip = 60;
const String _HttpContentType::ApplicationZip = createString("application/zip");    
const String _HttpContentType::SuffixZip = createString("zip");    

//application/octet-stream                         bin exe dll;
const int _HttpContentType::TypeApplicationOctetStream = 61;
const String _HttpContentType::ApplicationOctetStream = createString("application/octet-stream");    
const String _HttpContentType::SuffixBin = createString("bin");    
const String _HttpContentType::SuffixExe = createString("exe");    
const String _HttpContentType::SuffixDll = createString("dll");    
    
//application/octet-stream                         deb;
const String _HttpContentType::SuffixDeb = createString("deb");    

//application/octet-stream                         dmg;  
const String _HttpContentType::SuffixDmg = createString("dmg");    

//application/octet-stream                         iso img;
const String _HttpContentType::SuffixIso = createString("iso");    
const String _HttpContentType::SuffixImg = createString("img");    

//application/octet-stream                         msi msp msm;  
const String _HttpContentType::SuffixMsi = createString("msi");    
const String _HttpContentType::SuffixMsp = createString("msp");    
const String _HttpContentType::SuffixMsm = createString("msm");    

//audio/midi     mid midi kar;
const int _HttpContentType::TypeAudioMidi = 62;
const String _HttpContentType::AudioMidi = createString("audio/midi");    
const String _HttpContentType::SuffixMid = createString("mid");    
const String _HttpContentType::SuffixMidi = createString("midi");    
const String _HttpContentType::SuffixKar = createString("kar");    

//audio/mpeg     mp3;
const int _HttpContentType::TypeAudioMpeg = 63;
const String _HttpContentType::AudioMpeg = createString("audio/mpeg");    
const String _HttpContentType::SuffixMp3 = createString("mp3");    

//audio/ogg      ogg;
const int _HttpContentType::TypeAudioOgg = 64;
const String _HttpContentType::AudioOgg = createString("audio/ogg");    
const String _HttpContentType::SuffixOgg = createString("ogg");    

//audio/x-m4a    m4a;
const int _HttpContentType::TypeAudioXM4a = 65;
const String _HttpContentType::AudioXM4a = createString("audio/x-m4a");    
const String _HttpContentType::SuffixM4a = createString("m4a");    

//audio/x-realaudio                                ra;
const int _HttpContentType::TypeAudioXRealAudio = 66;
const String _HttpContentType::AudioXRealAudio = createString("audio/x-realaudio");    
const String _HttpContentType::SuffixRa = createString("ra");    

//video/3gpp     3gpp 3gp;
const int _HttpContentType::TypeVideo3Gpp = 67;
const String _HttpContentType::Video3Gpp = createString("video/3gpp");    
const String _HttpContentType::Suffix3Gpp = createString("3gpp");    
const String _HttpContentType::Sufix3Gp = createString("3gp");    

//video/mp2t     ts;
const int _HttpContentType::TypeVideoMp2t = 68;
const String _HttpContentType::VideoMp2t = createString("video/mp2t");    
const String _HttpContentType::SuffixTs = createString("ts");    

//video/mp4      mp4;
const int _HttpContentType::TypeVideoMp4 = 69;
const String _HttpContentType::VideoMp4 = createString("video/mp4");    
const String _HttpContentType::SuffixMp4 = createString("mp4");    

//video/mpeg     mpeg mpg;
const int _HttpContentType::TypeVideoMpeg = 70;
const String _HttpContentType::VideoMpeg = createString("video/mpeg");    
const String _HttpContentType::SuffixMpeg = createString("mpeg");    
const String _HttpContentType::SuffixMpg = createString("mpg");    

//video/quicktime                                  mov;
const int _HttpContentType::TypeVidoQuicktime = 71;
const String _HttpContentType::VidoQuicktime = createString("video/quicktime");    
const String _HttpContentType::SuffixMov = createString("mov");    

//video/webm     webm;
const int _HttpContentType::TypeVideoWebm = 72;
const String _HttpContentType::VideoWebm = createString("video/webm");    
const String _HttpContentType::SuffixWebm = createString("webm");    

//video/x-flv    flv;
const int _HttpContentType::TypeVideoXflv = 73;
const String _HttpContentType::VideoXflv = createString("video/x-flv");    
const String _HttpContentType::SuffixFlv = createString("flv");    

//video/x-m4v    m4v;
const int _HttpContentType::TypeVideoXM4v = 74;
const String _HttpContentType::VideoXM4v = createString("video/x-m4v");    
const String _HttpContentType::SuffixM4V = createString("m4v");    

//video/x-mng    mng;
const int _HttpContentType::TypeVideoXMng = 75;
const String _HttpContentType::VideoXMng = createString("video/x-mng");    
const String _HttpContentType::SuffixMng = createString("mng");    

//video/x-ms-asf    asx asf;
const int _HttpContentType::TypeVideoXMsAsf = 76;
const String _HttpContentType::VideoXMsAsf = createString("video/x-ms-asf");    
const String _HttpContentType::SuffixAsx = createString("asx");    
const String _HttpContentType::SuffixAsf = createString("asf");    

//video/x-ms-wmv    wmv;
const int _HttpContentType::TypeVideoXMsWmv = 77;
const String _HttpContentType::VideoXMsWmv = createString("video/x-ms-wmv");    
const String _HttpContentType::SuffixWmv = createString("wmv");    

//video/x-msvideo                                  avi;
const int _HttpContentType::TypeVideoXMsVideo = 78;
const String _HttpContentType::VideoXMsVideo = createString("video/x-msvideo");
const String _HttpContentType::SuffixAvi = createString("avi");

//multipart/form-data 
const int _HttpContentType::TypeMultiPartFormData = 79;
const String _HttpContentType::MultiPartFormData = createString("multipart/form-data");
const String _HttpContentType::FormData = createString("form-data");
const String _HttpContentType::Boundary = createString("boundary");


//x-www-form-urlencoded
const int _HttpContentType::TypeXFormUrlEncoded = 80;
const String _HttpContentType::XFormUrlEncoded = createString("application/x-www-form-urlencoded");

//CharSet
const String _HttpContentType::CharSet = createString("charset");

_HttpContentType::_HttpContentType() {
    mContentType = nullptr;
    mSubtype = nullptr;
    mSubValue = nullptr;
    mCharset = nullptr;
}

_HttpContentType::_HttpContentType(String value) {
    mContentType = nullptr;
    mSubtype = nullptr;
    mSubValue = nullptr;
    mCharset = nullptr;
    import(value);
}

void _HttpContentType::import(String value) {
    if(value != nullptr) {
        int pos = 0;
        while (pos < value->size()) {
            int tokenStart = pos;
            pos = st(HttpHeaderParser)::skipUntil(value, pos, "=,;");
            String directive = value->subString(tokenStart, pos-tokenStart)->trim();
            String parameter = nullptr;

            if (pos == value->size() || value->charAt(pos) == ',' || value->charAt(pos) == ';') {
                pos++; // consume ',' or ';' (if necessary)
                parameter = nullptr;
            } else {
                pos++; // consume '='
                pos = st(HttpHeaderParser)::skipWhitespace(value, pos);
                // quoted string
                if (pos < value->size() && value->charAt(pos) == '\"') {
                    pos++; // consume '"' open quote
                    int parameterStart = pos;
                    pos = st(HttpHeaderParser)::skipUntil(value, pos, "\"");
                    parameter = value->subString(parameterStart, pos);
                    pos++; // consume '"' close quote (if necessary)
                    // unquoted string
                } else {
                    int parameterStart = pos;
                    pos = st(HttpHeaderParser)::skipUntil(value, pos, ",;");
                    parameter = value->subString(parameterStart, (pos-parameterStart))->trim();
                    pos++;
                }
            }

            if(parameter == nullptr) {
                mContentType = directive;
            } else if(CharSet->equalsIgnoreCase(directive)) {
                this->mCharset = parameter;
            } else {
                mSubtype = directive;
                mSubValue = parameter;
                break;
            }
        }
    }
}

void _HttpContentType::setType(String value) {
    mContentType = value;
}

void _HttpContentType::setCharSet(String value) {
    mCharset = value;
}

void _HttpContentType::setBoundary(String value) {
    mSubtype = Boundary;
    mSubValue = value;
}

String _HttpContentType::getType() {
    return mContentType;
}

String _HttpContentType::getCharSet() {
    return mCharset;
}

String _HttpContentType::getBoundary() {
    return mSubValue;
}

String _HttpContentType::toString() {
    String result = mContentType;
    if(mCharset != nullptr) {
        result = result->append(";charset = ",mCharset);
    }
    if(mSubtype != nullptr) {
        result = result->append("; ",mSubtype," = ",mSubValue);
    }
    return result;
}

    

}
