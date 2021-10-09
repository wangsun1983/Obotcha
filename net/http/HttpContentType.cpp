#include "Object.hpp"
#include "StrongPointer.hpp"

#include "AutoLock.hpp"
#include "HttpContentType.hpp"
#include "HttpHeaderContentParser.hpp"
#include "String.hpp"

namespace obotcha {

// text/html(html htm shtml)
const String _HttpContentType::TextHtml =
    createString("text/html"); // text/html(html htm shtml)
const String _HttpContentType::SuffixHtml = createString("html");
const String _HttpContentType::SuffixHtm = createString("htm");
const String _HttpContentType::SuffixShtml = createString("shtml");

// text/css(css)
const String _HttpContentType::TextCss = createString("text/css");
const String _HttpContentType::SuffixCss = createString("css");

// text/xml(xml)
const String _HttpContentType::TextXml = createString("text/xml");
const String _HttpContentType::SuffixXml = createString("xml");

// image/gif(gif)
const String _HttpContentType::ImageGif = createString("image/gif");
const String _HttpContentType::SuffixGif = createString("gif");

// image/jpeg(jpeg jpg)
const String _HttpContentType::ImageJpeg = createString("image/jpeg");
const String _HttpContentType::SuffixJpeg = createString("jpeg");
const String _HttpContentType::SuffixJpg = createString("jpg");

// application/javascript(js)
const String _HttpContentType::ApplicationJs =
    createString("application/javascript");
const String _HttpContentType::SuffixJs = createString("js");

// application/atom+xml(atom)
const String _HttpContentType::ApplicationAtomXml =
    createString("application/atom+xml");
const String _HttpContentType::SuffixAtom = createString("atom");

// application/rss+xml(rss)
const String _HttpContentType::ApplicationRss =
    createString("application/rss+xml");
const String _HttpContentType::SuffixRss = createString("rss");

// text/mathml(mml)
const String _HttpContentType::TextMathml = createString("text/mathml");
const String _HttpContentType::SuffixMml = createString("mml");

// text/plain(txt)
const String _HttpContentType::TextPlain = createString("text/plain");
const String _HttpContentType::SuffixTxt = createString("txt");

// text/vnd.sun.j2me.app-descriptor(jad)
const String _HttpContentType::TextVndSunJ2meAppDes =
    createString("text/vnd.sun.j2me.app-descriptor");
const String _HttpContentType::SuffixJad = createString("jad");

// text/vnd.wap.wml                                 wml;
const String _HttpContentType::TextVndWapWml = createString("text/vnd.wap.wml");
const String _HttpContentType::SuffixWml = createString("wml");

// text/x-component                                 htc;
const String _HttpContentType::TextXComponent =
    createString("text/x-component");
const String _HttpContentType::SuffixHtc = createString("htc");

// image/png      png;
const String _HttpContentType::ImagePng = createString("image/png");
const String _HttpContentType::SuffixPng = createString("png");

// image/svg+xml     svg svgz;
const String _HttpContentType::ImageSvgXml = createString("image/svg+xml");
const String _HttpContentType::SuffixSvg = createString("svg");
const String _HttpContentType::SuffixSvgz = createString("svgz");

// image/tiff     tif tiff;
const String _HttpContentType::ImageTiff = createString("image/tiff");
const String _HttpContentType::SuffixTif = createString("tif");
const String _HttpContentType::SuffixTiff = createString("tiff");

// image/vnd.wap.wbmp                               wbmp;
const String _HttpContentType::ImageVndWapWbmp =
    createString("image/vnd.wap.wbmp");
const String _HttpContentType::SuffixWbmp = createString("wbmp");

// image/webp     webp;
const String _HttpContentType::ImageWebp = createString("image/webp");
const String _HttpContentType::SuffixWebp = createString("webp");

// image/x-icon      ico;
const String _HttpContentType::ImageXIcon = createString("image/x-icon");
const String _HttpContentType::SuffixIco = createString("ico");

// image/x-jng    jng;
const String _HttpContentType::ImageXJng = createString("image/x-jng");
const String _HttpContentType::SuffixJng = createString("jng");

// image/x-ms-bmp    bmp;
const String _HttpContentType::ImageXMsBmp = createString("image/x-ms-bmp");
const String _HttpContentType::SuffixBmp = createString("bmp");

// application/font-woff                            woff;
const String _HttpContentType::ApplicationFontWoff =
    createString("application/font-woff");
const String _HttpContentType::SuffixWoff = createString("woff");

// application/java-archive                         jar war ear;
const String _HttpContentType::ApplicationJavaArchive =
    createString("application/java-archive");
const String _HttpContentType::SuffixJar = createString("jar");
const String _HttpContentType::SuffixWar = createString("war");
const String _HttpContentType::SuffixEar = createString("ear");

// application/json                                 json;
const String _HttpContentType::ApplicationJson =
    createString("application/json");
const String _HttpContentType::SuffixJson = createString("json");

// application/mac-binhex40                         hqx;
const String _HttpContentType::ApplicationMaxBinhex40 =
    createString("application/mac-binhex40");
const String _HttpContentType::SuffixHqx = createString("hqx");

// application/msword                               doc;
const String _HttpContentType::ApplicationMsword =
    createString("application/msword");
const String _HttpContentType::SuffixDoc = createString("doc");

// application/pdf                                  pdf;
const String _HttpContentType::ApplicationPdf = createString("application/pdf");
const String _HttpContentType::SuffixPdf = createString("pdf");

// application/postscript                           ps eps ai;
const String _HttpContentType::ApplicationPostScript =
    createString("application/postscript");
const String _HttpContentType::SuffixPs = createString("ps");
const String _HttpContentType::SuffixEps = createString("eps");
const String _HttpContentType::SuffixAi = createString("ai");

// application/rtf                                  rtf;
const String _HttpContentType::ApplicationRtf = createString("application/rtf");
const String _HttpContentType::SuffixRtf = createString("rtf");

// application/vnd.apple.mpegurl                    m3u8;
const String _HttpContentType::ApplicationVndAppleMpegurl =
    createString("application/vnd.apple.mpegurl");
const String _HttpContentType::SuffixM3u8 = createString("m3u8");

// application/vnd.google-earth.kml+xml             kml;
const String _HttpContentType::ApplicationVndGoogleEarthKmlXml =
    createString("application/vnd.google-earth.kml+xml");
const String _HttpContentType::SuffixKml = createString("kml");

// application/vnd.google-earth.kmz                 kmz;
const String _HttpContentType::ApplicationVndGoogleEarthKmz =
    createString("application/vnd.google-earth.kmz");
const String _HttpContentType::SuffixKmz = createString("kmz");

// application/vnd.ms-excel                         xls;
const String _HttpContentType::ApplicationVndMsExcel =
    createString("application/vnd.ms-excel");
const String _HttpContentType::SuffixXls = createString("xls");

// application/vnd.ms-fontobject                    eot;
const String _HttpContentType::ApplicationVndMsFontObject =
    createString("application/vnd.ms-fontobject");
const String _HttpContentType::SuffixEot = createString("eot");

// application/vnd.ms-powerpoint                    ppt;
const String _HttpContentType::ApplicationVndMsPpt =
    createString("application/vnd.ms-powerpoint");
const String _HttpContentType::SuffixPpt = createString("ppt");

// application/vnd.oasis.opendocument.graphics      odg;
const String _HttpContentType::ApplicationVndOasisOpendocGraphics =
    createString("application/vnd.oasis.opendocument.graphics");
const String _HttpContentType::SuffixOdj = createString("odg");

// application/vnd.oasis.opendocument.presentation  odp;
const String _HttpContentType::ApplicationVndOasisOpendocPresentation =
    createString("application/vnd.oasis.opendocument.presentation");
const String _HttpContentType::SuffixOdp = createString("odp");

// application/vnd.oasis.opendocument.spreadsheet   ods;
const String _HttpContentType::ApplicationVndOasisOpendocSpreadsheet =
    createString("application/vnd.oasis.opendocument.spreadsheet");
const String _HttpContentType::SuffixOds = createString("ods");

// application/vnd.oasis.opendocument.text          odt;
const String _HttpContentType::ApplicationVndOasisOpendocText =
    createString("application/vnd.oasis.opendocument.text");
const String _HttpContentType::SuffixOdt = createString("odt");

// application/vnd.openxmlformats-officedocument.presentationml.presentation
// pptx;
const String _HttpContentType::ApplicationVndOpenxmlPresentation = createString(
    "application/"
    "vnd.openxmlformats-officedocument.presentationml.presentation");
const String _HttpContentType::SuffixPptx = createString("pptx");

// application/vnd.openxmlformats-officedocument.spreadsheetml.sheet
//               xlsx;
const String _HttpContentType::ApplicationVndOpenXmlSheet = createString(
    "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
const String _HttpContentType::SuffixXlsx = createString("xlsx");

// application/vnd.openxmlformats-officedocument.wordprocessingml.document
//               docx;
const String _HttpContentType::ApplicationVndOepnXmlDoc = createString(
    "application/vnd.openxmlformats-officedocument.wordprocessingml.document");
const String _HttpContentType::SuffixDocx = createString("docx");

// application/vnd.wap.wmlc                         wmlc;
const String _HttpContentType::ApplicationVndWapWmls =
    createString("application/vnd.wap.wmlc");
const String _HttpContentType::SuffixWmlc = createString("wmlc");

// application/x-7z-compressed                      7z;
const String _HttpContentType::Application7z =
    createString("application/x-7z-compressed");
const String _HttpContentType::Suffix7z = createString("7z");

// application/x-cocoa                              cco;
const String _HttpContentType::ApplicationXCocoa =
    createString("application/x-cocoa");
const String _HttpContentType::SuffixCco = createString("cco");

// application/x-java-archive-diff                  jardiff;
const String _HttpContentType::ApplicationXJavaArch =
    createString("application/x-java-archive-diff");
const String _HttpContentType::SuffixJardiff = createString("jardiff");

// application/x-java-jnlp-file                     jnlp;
const String _HttpContentType::ApplicationXJavaJnlpFile =
    createString("application/x-java-jnlp-file");
const String _HttpContentType::SuffixJnlp = createString("jnlp");

// application/x-makeself                           run;
const String _HttpContentType::ApplicationXMakeself =
    createString("application/x-makeself");
const String _HttpContentType::SuffixRun = createString("run");

// application/x-perl                               pl pm;
const String _HttpContentType::ApplicationXPerl =
    createString("application/x-perl");
const String _HttpContentType::SuffixPl = createString("pl");
const String _HttpContentType::SuffixPm = createString("pm");

// application/x-pilot                              prc pdb;
const String _HttpContentType::ApplicationXPilot =
    createString("application/x-pilot");
const String _HttpContentType::SuffixPrc = createString("prc");
const String _HttpContentType::SuffixPdb = createString("pdb");

// application/x-rar-compressed                     rar;
const String _HttpContentType::ApplicationXRarCompressed =
    createString("application/x-rar-compressed");
const String _HttpContentType::SuffixRar = createString("rar");

// application/x-redhat-package-manager             rpm;
const String _HttpContentType::ApplicationXReadhatPkgManager =
    createString("application/x-redhat-package-manager");
const String _HttpContentType::SuffixRpm = createString("rpm");

// application/x-sea                                sea;
const String _HttpContentType::ApplicationXSea =
    createString("application/x-sea");
const String _HttpContentType::SuffixSea = createString("sea");

// application/x-shockwave-flash                    swf;
const String _HttpContentType::ApplicationXShockwaveFlash =
    createString("application/x-shockwave-flash");
const String _HttpContentType::SuffixSwf = createString("swf");

// application/x-stuffit                            sit;
const String _HttpContentType::ApplicationXStuffit =
    createString("application/x-stuffit");
const String _HttpContentType::SuffixSit = createString("sit");

// application/x-tcl                                tcl tk;
const String _HttpContentType::ApplicationXTcl =
    createString("application/x-tcl");
const String _HttpContentType::SuffixTcl = createString("tcl");
const String _HttpContentType::SuffixTk = createString("tk");

// application/x-x509-ca-cert                       der pem crt;
const String _HttpContentType::ApplicationXX509CaCert =
    createString("application/x-x509-ca-cert");
const String _HttpContentType::SuffixDer = createString("der");
const String _HttpContentType::SuffixPem = createString("pem");
const String _HttpContentType::SuffixCrt = createString("crt");

// application/x-xpinstall                          xpi;
const String _HttpContentType::ApplicationXXpinstall =
    createString("application/x-xpinstall");
const String _HttpContentType::SuffixXpi = createString("xpi");

// application/xhtml+xml                            xhtml;
const String _HttpContentType::ApplicationXhtmlXml =
    createString("application/xhtml+xml");
const String _HttpContentType::SuffixXhtml = createString("xhtml");

// application/xspf+xml                             xspf;
const String _HttpContentType::ApplicationXspfXml =
    createString("application/xspf+xml");
const String _HttpContentType::SuffixXspf = createString("xspf");

// application/zip                                  zip;
const String _HttpContentType::ApplicationZip = createString("application/zip");
const String _HttpContentType::SuffixZip = createString("zip");

// application/octet-stream                         bin exe dll;
const String _HttpContentType::ApplicationOctetStream =
    createString("application/octet-stream");
const String _HttpContentType::SuffixBin = createString("bin");
const String _HttpContentType::SuffixExe = createString("exe");
const String _HttpContentType::SuffixDll = createString("dll");

// application/octet-stream                         deb;
const String _HttpContentType::SuffixDeb = createString("deb");

// application/octet-stream                         dmg;
const String _HttpContentType::SuffixDmg = createString("dmg");

// application/octet-stream                         iso img;
const String _HttpContentType::SuffixIso = createString("iso");
const String _HttpContentType::SuffixImg = createString("img");

// application/octet-stream                         msi msp msm;
const String _HttpContentType::SuffixMsi = createString("msi");
const String _HttpContentType::SuffixMsp = createString("msp");
const String _HttpContentType::SuffixMsm = createString("msm");

// audio/midi     mid midi kar;
const String _HttpContentType::AudioMidi = createString("audio/midi");
const String _HttpContentType::SuffixMid = createString("mid");
const String _HttpContentType::SuffixMidi = createString("midi");
const String _HttpContentType::SuffixKar = createString("kar");

// audio/mpeg     mp3;
const String _HttpContentType::AudioMpeg = createString("audio/mpeg");
const String _HttpContentType::SuffixMp3 = createString("mp3");

// audio/ogg      ogg;
const String _HttpContentType::AudioOgg = createString("audio/ogg");
const String _HttpContentType::SuffixOgg = createString("ogg");

// audio/x-m4a    m4a;
const String _HttpContentType::AudioXM4a = createString("audio/x-m4a");
const String _HttpContentType::SuffixM4a = createString("m4a");

// audio/x-realaudio                                ra;
const String _HttpContentType::AudioXRealAudio =
    createString("audio/x-realaudio");
const String _HttpContentType::SuffixRa = createString("ra");

// video/3gpp     3gpp 3gp;
const String _HttpContentType::Video3Gpp = createString("video/3gpp");
const String _HttpContentType::Suffix3Gpp = createString("3gpp");
const String _HttpContentType::Sufix3Gp = createString("3gp");

// video/mp2t     ts;
const String _HttpContentType::VideoMp2t = createString("video/mp2t");
const String _HttpContentType::SuffixTs = createString("ts");

// video/mp4      mp4;
const String _HttpContentType::VideoMp4 = createString("video/mp4");
const String _HttpContentType::SuffixMp4 = createString("mp4");

// video/mpeg     mpeg mpg;
const String _HttpContentType::VideoMpeg = createString("video/mpeg");
const String _HttpContentType::SuffixMpeg = createString("mpeg");
const String _HttpContentType::SuffixMpg = createString("mpg");

// video/quicktime                                  mov;
const String _HttpContentType::VidoQuicktime = createString("video/quicktime");
const String _HttpContentType::SuffixMov = createString("mov");

// video/webm     webm;
const String _HttpContentType::VideoWebm = createString("video/webm");
const String _HttpContentType::SuffixWebm = createString("webm");

// video/x-flv    flv;
const String _HttpContentType::VideoXflv = createString("video/x-flv");
const String _HttpContentType::SuffixFlv = createString("flv");

// video/x-m4v    m4v;
const String _HttpContentType::VideoXM4v = createString("video/x-m4v");
const String _HttpContentType::SuffixM4V = createString("m4v");

// video/x-mng    mng;
const String _HttpContentType::VideoXMng = createString("video/x-mng");
const String _HttpContentType::SuffixMng = createString("mng");

// video/x-ms-asf    asx asf;
const String _HttpContentType::VideoXMsAsf = createString("video/x-ms-asf");
const String _HttpContentType::SuffixAsx = createString("asx");
const String _HttpContentType::SuffixAsf = createString("asf");

// video/x-ms-wmv    wmv;
const String _HttpContentType::VideoXMsWmv = createString("video/x-ms-wmv");
const String _HttpContentType::SuffixWmv = createString("wmv");

// video/x-msvideo                                  avi;
const String _HttpContentType::VideoXMsVideo = createString("video/x-msvideo");
const String _HttpContentType::SuffixAvi = createString("avi");

// multipart/form-data
const String _HttpContentType::MultiPartFormData =
    createString("multipart/form-data");
const String _HttpContentType::FormData = createString("form-data");
const String _HttpContentType::Boundary = createString("boundary");

// x-www-form-urlencoded
const String _HttpContentType::XFormUrlEncoded =
    createString("application/x-www-form-urlencoded");

// CharSet
const String _HttpContentType::CharSet = createString("charset");

_HttpContentType::_HttpContentType() {
    mContentType = nullptr;
    mBoundary = nullptr;
    mCharset = nullptr;
}

_HttpContentType::_HttpContentType(String value) {
    mContentType = nullptr;
    mBoundary = nullptr;
    mCharset = nullptr;
    import(value);
}

void _HttpContentType::import(String value) {
    st(HttpHeaderContentParser)::import(value,[this](String directive,String parameter) {
        if (parameter == nullptr) {
            mContentType = directive;
        } else if (CharSet->equalsIgnoreCase(directive)) {
            mCharset = parameter;
        } else if(Boundary->equalsIgnoreCase(directive)) {
            mBoundary = parameter;
        }
    });
}

void _HttpContentType::setType(String value) { mContentType = value; }

void _HttpContentType::setCharSet(String value) { mCharset = value; }

void _HttpContentType::setBoundary(String value) {
    mBoundary = value;
}

String _HttpContentType::getType() { return mContentType; }

String _HttpContentType::getCharSet() { return mCharset; }

String _HttpContentType::getBoundary() { return mBoundary; }

String _HttpContentType::toString() {
    String result = mContentType;
    printf("mContentType is %s \n",mContentType->toChars());
    if (mCharset != nullptr) {
        printf("trace1 \n");
        result = result->append(";charset=", mCharset);
    }
    if (mBoundary != nullptr) {
        printf("trace2 \n");
        result = result->append(";boundary=", mBoundary);
    }
    return result;
}

} // namespace obotcha
