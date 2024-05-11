// according nginx/conf/mime.types
#include "HttpMime.hpp"
#include "Log.hpp"

namespace obotcha {

HashMap<String,Integer> _HttpMime::nameToId = nullptr;
HashMap<String,Integer> _HttpMime::suffixToId = nullptr;

/**
* type:
* text/html
* suffix:
* html,htm,shtml
**/ 
const String _HttpMime::TextHtml = String::New("text/html");
const String _HttpMime::SuffixHtml = String::New("html");
const String _HttpMime::SuffixHtm = String::New("htm");
const String _HttpMime::SuffixShtml = String::New("shtml");

/**
* type:
* text/css
* suffix:
* css
**/ 
const String _HttpMime::TextCss = String::New("text/css");
const String _HttpMime::SuffixCss = String::New("css");

/**
* type:
* text/xml
* suffix:
* xml
**/ 
const String _HttpMime::TextXml = String::New("text/xml");
const String _HttpMime::SuffixXml = String::New("xml");

/**
* type:
* image/gif
* suffix:
* gif
**/ 
const String _HttpMime::ImageGif = String::New("image/gif");
const String _HttpMime::SuffixGif = String::New("gif");

/**
* type:
* image/jpeg
* suffix:
* jpeg or jpg
**/ 
const String _HttpMime::ImageJpeg = String::New("image/jpeg");
const String _HttpMime::SuffixJpeg = String::New("jpeg");
const String _HttpMime::SuffixJpg = String::New("jpg");

/**
* type:
* application/javascript
* suffix:
* js
**/
const String _HttpMime::ApplicationJs = String::New("application/javascript");
const String _HttpMime::SuffixJs = String::New("js");

/**
* type:
* application/atom+xml
* suffix:
* atom
**/
const String _HttpMime::ApplicationAtomXml = String::New("application/atom+xml");
const String _HttpMime::SuffixAtom = String::New("atom");

/**
* type:
* application/rss+xml
* suffix:
* rss
**/
const String _HttpMime::ApplicationRss = String::New("application/rss+xml");
const String _HttpMime::SuffixRss = String::New("rss");

/**
* type:
* text/mathml
* suffix:
* mml
**/
const String _HttpMime::TextMathml = String::New("text/mathml");
const String _HttpMime::SuffixMml = String::New("mml");

/**
* type:
* text/plain
* suffix:
* txt
**/
const String _HttpMime::TextPlain = String::New("text/plain");
const String _HttpMime::SuffixTxt = String::New("txt");

/**
* type:
* text/vnd.sun.j2me.app-descriptor
* suffix:
* jad
**/
const String _HttpMime::TextVndSunJ2meAppDes = String::New("text/vnd.sun.j2me.app-descriptor");
const String _HttpMime::SuffixJad = String::New("jad");

/**
* type:
* text/vnd.wap.wml
* suffix:
* wml
**/
const String _HttpMime::TextVndWapWml = String::New("text/vnd.wap.wml");
const String _HttpMime::SuffixWml = String::New("wml");

/**
* type:
* text/x-component
* suffix:
* htc
**/
const String _HttpMime::TextXComponent = String::New("text/x-component");
const String _HttpMime::SuffixHtc = String::New("htc");

/**
* type:
* image/png
* suffix:
* png
**/
const String _HttpMime::ImagePng = String::New("image/png");
const String _HttpMime::SuffixPng = String::New("png");

/**
* type:
* image/svg+xml
* suffix:
* svg or svgz
**/
const String _HttpMime::ImageSvgXml = String::New("image/svg+xml");
const String _HttpMime::SuffixSvg = String::New("svg");
const String _HttpMime::SuffixSvgz = String::New("svgz");

/**
* type:
* image/tiff
* suffix:
* tif or tiff
**/
const String _HttpMime::ImageTiff = String::New("image/tiff");
const String _HttpMime::SuffixTif = String::New("tif");
const String _HttpMime::SuffixTiff = String::New("tiff");

/**
* type:
* image/vnd.wap.wbmp
* suffix:
* wbmp
**/
const String _HttpMime::ImageVndWapWbmp = String::New("image/vnd.wap.wbmp");
const String _HttpMime::SuffixWbmp = String::New("wbmp");

/**
* type:
* image/webp
* suffix:
* webp
**/
const String _HttpMime::ImageWebp = String::New("image/webp");
const String _HttpMime::SuffixWebp = String::New("webp");

/**
* type:
* image/x-icon
* suffix:
* ico
**/
const String _HttpMime::ImageXIcon = String::New("image/x-icon");
const String _HttpMime::SuffixIco = String::New("ico");

/**
* type:
* image/x-jng
* suffix:
* jng
**/
const String _HttpMime::ImageXJng = String::New("image/x-jng");
const String _HttpMime::SuffixJng = String::New("jng");

/**
* type:
* image/x-ms-bmp
* suffix:
* bmp
**/
const String _HttpMime::ImageXMsBmp = String::New("image/x-ms-bmp");
const String _HttpMime::SuffixBmp = String::New("bmp");

/**
* type:
* application/font-woff
* suffix:
* woff
**/
const String _HttpMime::ApplicationFontWoff = String::New("application/font-woff");
const String _HttpMime::SuffixWoff = String::New("woff");

/**
* type:
* application/java-archive
* suffix:
* jar or war or ear
**/
const String _HttpMime::ApplicationJavaArchive = String::New("application/java-archive");
const String _HttpMime::SuffixJar = String::New("jar");
const String _HttpMime::SuffixWar = String::New("war");
const String _HttpMime::SuffixEar = String::New("ear");

/**
* type:
* application/json
* suffix:
* json
**/
const String _HttpMime::ApplicationJson = String::New("application/json");
const String _HttpMime::SuffixJson = String::New("json");

/**
* type:
* application/mac-binhex40
* suffix:
* hqx
**/
const String _HttpMime::ApplicationMaxBinhex40 = String::New("application/mac-binhex40");
const String _HttpMime::SuffixHqx = String::New("hqx");

/**
* type:
* application/msword
* suffix:
* doc
**/
const String _HttpMime::ApplicationMsword = String::New("application/msword");
const String _HttpMime::SuffixDoc = String::New("doc");

/**
* type:
* application/pdf
* suffix:
* pdf
**/
const String _HttpMime::ApplicationPdf = String::New("application/pdf");
const String _HttpMime::SuffixPdf = String::New("pdf");

/**
* type:
* application/postscript
* suffix:
* ps or eps or ai
**/
const String _HttpMime::ApplicationPostScript = String::New("application/postscript");
const String _HttpMime::SuffixPs = String::New("ps");
const String _HttpMime::SuffixEps = String::New("eps");
const String _HttpMime::SuffixAi = String::New("ai");

/**
* type:
* application/rtf
* suffix:
* rtf
**/
const String _HttpMime::ApplicationRtf = String::New("application/rtf");
const String _HttpMime::SuffixRtf = String::New("rtf");

/**
* type:
* application/vnd.apple.mpegurl
* suffix:
* m3u8
**/
const String _HttpMime::ApplicationVndAppleMpegurl = String::New("application/vnd.apple.mpegurl");
const String _HttpMime::SuffixM3u8 = String::New("m3u8");

/**
* type:
* application/vnd.google-earth.kml+xml
* suffix:
* kml
**/
const String _HttpMime::ApplicationVndGoogleEarthKmlXml = String::New("application/vnd.google-earth.kml+xml");
const String _HttpMime::SuffixKml = String::New("kml");

/**
* type:
* application/vnd.google-earth.kmz
* suffix:
* kmz
**/
const String _HttpMime::ApplicationVndGoogleEarthKmz = String::New("application/vnd.google-earth.kmz");
const String _HttpMime::SuffixKmz = String::New("kmz");

/**
* type:
* application/vnd.ms-excel
* suffix:
* xls
**/
const String _HttpMime::ApplicationVndMsExcel = String::New("application/vnd.ms-excel");
const String _HttpMime::SuffixXls = String::New("xls");

/**
* type:
* application/vnd.ms-fontobject
* suffix:
* eot
**/
const String _HttpMime::ApplicationVndMsFontObject = String::New("application/vnd.ms-fontobject");
const String _HttpMime::SuffixEot = String::New("eot");

/**
* type:
* application/vnd.ms-powerpoint
* suffix:
* ppt
**/
const String _HttpMime::ApplicationVndMsPpt = String::New("application/vnd.ms-powerpoint");
const String _HttpMime::SuffixPpt = String::New("ppt");

/**
* type:
* application/vnd.oasis.opendocument.graphics
* suffix:
* odg
**/
const String _HttpMime::ApplicationVndOasisOpendocGraphics = String::New("application/vnd.oasis.opendocument.graphics");
const String _HttpMime::SuffixOdj = String::New("odg");

/**
* type:
* application/vnd.oasis.opendocument.presentation
* suffix:
* odp
**/
const String _HttpMime::ApplicationVndOasisOpendocPresentation = String::New("application/vnd.oasis.opendocument.presentation");
const String _HttpMime::SuffixOdp = String::New("odp");

/**
* type:
* application/vnd.oasis.opendocument.spreadsheet
* suffix:
* ods
**/
const String _HttpMime::ApplicationVndOasisOpendocSpreadsheet = String::New("application/vnd.oasis.opendocument.spreadsheet");
const String _HttpMime::SuffixOds = String::New("ods");

/**
* type:
* application/vnd.oasis.opendocument.text
* suffix:
* odt
**/
const String _HttpMime::ApplicationVndOasisOpendocText = String::New("application/vnd.oasis.opendocument.text");
const String _HttpMime::SuffixOdt = String::New("odt");

/**
* type:
* application/vnd.openxmlformats-officedocument.presentationml.presentation
* suffix:
* pptx
**/
const String _HttpMime::ApplicationVndOpenxmlPresentation = String::New(
    "application/vnd.openxmlformats-officedocument.presentationml.presentation");
const String _HttpMime::SuffixPptx = String::New("pptx");

/**
* type:
* application/vnd.openxmlformats-officedocument.spreadsheetml.sheet
* suffix:
* xlsx
**/
const String _HttpMime::ApplicationVndOpenXmlSheet = String::New(
    "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
const String _HttpMime::SuffixXlsx = String::New("xlsx");

/**
* type:
* application/vnd.openxmlformats-officedocument.wordprocessingml.document
* suffix:
* docx
**/
const String _HttpMime::ApplicationVndOepnXmlDoc = String::New(
    "application/vnd.openxmlformats-officedocument.wordprocessingml.document");
const String _HttpMime::SuffixDocx = String::New("docx");

/**
* type:
* application/vnd.wap.wmlc 
* suffix:
* wmlc
**/
const String _HttpMime::ApplicationVndWapWmls = String::New("application/vnd.wap.wmlc");
const String _HttpMime::SuffixWmlc = String::New("wmlc");

/**
* type:
* application/x-7z-compressed
* suffix:
* 7z
**/
const String _HttpMime::Application7z = String::New("application/x-7z-compressed");
const String _HttpMime::Suffix7z = String::New("7z");

/**
* type:
* application/x-cocoa
* suffix:
* cco
**/
const String _HttpMime::ApplicationXCocoa = String::New("application/x-cocoa");
const String _HttpMime::SuffixCco = String::New("cco");

/**
* type:
* application/x-java-archive-diff
* suffix:
* jardiff
**/
const String _HttpMime::ApplicationXJavaArch = String::New("application/x-java-archive-diff");
const String _HttpMime::SuffixJardiff = String::New("jardiff");

/**
* type:
* application/x-java-jnlp-file
* suffix:
* jnlp
**/
const String _HttpMime::ApplicationXJavaJnlpFile = String::New("application/x-java-jnlp-file");
const String _HttpMime::SuffixJnlp = String::New("jnlp");

/**
* type:
* application/x-makeself
* suffix:
* run
**/
const String _HttpMime::ApplicationXMakeself = String::New("application/x-makeself");
const String _HttpMime::SuffixRun = String::New("run");

/**
* type:
* application/x-perl
* suffix:
* pl or pm
**/
const String _HttpMime::ApplicationXPerl = String::New("application/x-perl");
const String _HttpMime::SuffixPl = String::New("pl");
const String _HttpMime::SuffixPm = String::New("pm");

/**
* type:
* application/x-pilot
* suffix:
* prc or pdb
**/
const String _HttpMime::ApplicationXPilot = String::New("application/x-pilot");
const String _HttpMime::SuffixPrc = String::New("prc");
const String _HttpMime::SuffixPdb = String::New("pdb");

/**
* type:
* application/x-rar-compressed
* suffix:
* rar
**/
const String _HttpMime::ApplicationXRarCompressed = String::New("application/x-rar-compressed");
const String _HttpMime::SuffixRar = String::New("rar");

/**
* type:
* application/x-redhat-package-manager
* suffix:
* rpm
**/
const String _HttpMime::ApplicationXReadhatPkgManager = String::New("application/x-redhat-package-manager");
const String _HttpMime::SuffixRpm = String::New("rpm");

/**
* type:
* application/x-sea
* suffix:
* sea
**/
const String _HttpMime::ApplicationXSea = String::New("application/x-sea");
const String _HttpMime::SuffixSea = String::New("sea");

/**
* type:
* application/x-shockwave-flash
* suffix:
* swf
**/
const String _HttpMime::ApplicationXShockwaveFlash = String::New("application/x-shockwave-flash");
const String _HttpMime::SuffixSwf = String::New("swf");

/**
* type:
* application/x-stuffit
* suffix:
* sit
**/
const String _HttpMime::ApplicationXStuffit = String::New("application/x-stuffit");
const String _HttpMime::SuffixSit = String::New("sit");

/**
* type:
* application/x-tcl
* suffix:
* tcl or tk
**/
const String _HttpMime::ApplicationXTcl = String::New("application/x-tcl");
const String _HttpMime::SuffixTcl = String::New("tcl");
const String _HttpMime::SuffixTk = String::New("tk");

/**
* type:
* application/x-x509-ca-cert
* suffix:
* der or pem or crt
**/
const String _HttpMime::ApplicationXX509CaCert = String::New("application/x-x509-ca-cert");
const String _HttpMime::SuffixDer = String::New("der");
const String _HttpMime::SuffixPem = String::New("pem");
const String _HttpMime::SuffixCrt = String::New("crt");

/**
* type:
* application/x-xpinstall
* suffix:
* xpi
**/
const String _HttpMime::ApplicationXXpinstall = String::New("application/x-xpinstall");
const String _HttpMime::SuffixXpi = String::New("xpi");

/**
* type:
* application/xhtml+xml
* suffix:
* xhtml
**/
const String _HttpMime::ApplicationXhtmlXml = String::New("application/xhtml+xml");
const String _HttpMime::SuffixXhtml = String::New("xhtml");

/**
* type:
* application/xspf+xml 
* suffix:
* xspf
**/
const String _HttpMime::ApplicationXspfXml = String::New("application/xspf+xml");
const String _HttpMime::SuffixXspf = String::New("xspf");

/**
* type:
* application/zip
* suffix:
* zip
**/
const String _HttpMime::ApplicationZip = String::New("application/zip");
const String _HttpMime::SuffixZip = String::New("zip");

/**
* type:
* application/octet-stream
* suffix:
* bin exe dll deb dmg iso img msi msp msm
**/
const String _HttpMime::ApplicationOctetStream = String::New("application/octet-stream");
const String _HttpMime::SuffixBin = String::New("bin");
const String _HttpMime::SuffixExe = String::New("exe");
const String _HttpMime::SuffixDll = String::New("dll");
const String _HttpMime::SuffixDeb = String::New("deb");
const String _HttpMime::SuffixDmg = String::New("dmg");
const String _HttpMime::SuffixIso = String::New("iso");
const String _HttpMime::SuffixImg = String::New("img");
const String _HttpMime::SuffixMsi = String::New("msi");
const String _HttpMime::SuffixMsp = String::New("msp");
const String _HttpMime::SuffixMsm = String::New("msm");

/**
* type:
* audio/midi
* suffix:
* mid or midi or kar
**/
const String _HttpMime::AudioMidi = String::New("audio/midi");
const String _HttpMime::SuffixMid = String::New("mid");
const String _HttpMime::SuffixMidi = String::New("midi");
const String _HttpMime::SuffixKar = String::New("kar");

/**
* type:
* audio/mpeg
* suffix:
* mp3
**/
const String _HttpMime::AudioMpeg = String::New("audio/mpeg");
const String _HttpMime::SuffixMp3 = String::New("mp3");

/**
* type:
* audio/ogg
* suffix:
* ogg
**/
const String _HttpMime::AudioOgg = String::New("audio/ogg");
const String _HttpMime::SuffixOgg = String::New("ogg");

/**
* type:
* audio/x-m4a
* suffix:
* m4a
**/
const String _HttpMime::AudioXM4a = String::New("audio/x-m4a");
const String _HttpMime::SuffixM4a = String::New("m4a");

/**
* type:
* audio/x-realaudio   
* suffix:
* ra
**/
const String _HttpMime::AudioXRealAudio = String::New("audio/x-realaudio");
const String _HttpMime::SuffixRa = String::New("ra");

/**
* type:
* video/3gpp
* suffix:
* 3gpp or 3gp
**/
const String _HttpMime::Video3Gpp = String::New("video/3gpp");
const String _HttpMime::Suffix3Gpp = String::New("3gpp");
const String _HttpMime::Sufix3Gp = String::New("3gp");

/**
* type:
* video/mp2t
* suffix:
* ts
**/
const String _HttpMime::VideoMp2t = String::New("video/mp2t");
const String _HttpMime::SuffixTs = String::New("ts");

/**
* type:
* video/mp4
* suffix:
* mp4
**/
const String _HttpMime::VideoMp4 = String::New("video/mp4");
const String _HttpMime::SuffixMp4 = String::New("mp4");

/**
* type:
* video/mpeg
* suffix:
* mpeg or mpg
**/
const String _HttpMime::VideoMpeg = String::New("video/mpeg");
const String _HttpMime::SuffixMpeg = String::New("mpeg");
const String _HttpMime::SuffixMpg = String::New("mpg");

/**
* type:
* video/quicktime
* suffix:
* mov
**/
const String _HttpMime::VidoQuicktime = String::New("video/quicktime");
const String _HttpMime::SuffixMov = String::New("mov");

/**
* type:
* video/webm 
* suffix:
* webm
**/
const String _HttpMime::VideoWebm = String::New("video/webm");
const String _HttpMime::SuffixWebm = String::New("webm");

/**
* type:
* video/x-flv
* suffix:
* flv
**/
const String _HttpMime::VideoXflv = String::New("video/x-flv");
const String _HttpMime::SuffixFlv = String::New("flv");

/**
* type:
* video/x-m4v
* suffix:
* m4v
**/
const String _HttpMime::VideoXM4v = String::New("video/x-m4v");
const String _HttpMime::SuffixM4V = String::New("m4v");

/**
* type:
* video/x-mng
* suffix:
* mng
**/
const String _HttpMime::VideoXMng = String::New("video/x-mng");
const String _HttpMime::SuffixMng = String::New("mng");

/**
* type:
* video/x-ms-asf
* suffix:
* asx or asf
**/
const String _HttpMime::VideoXMsAsf = String::New("video/x-ms-asf");
const String _HttpMime::SuffixAsx = String::New("asx");
const String _HttpMime::SuffixAsf = String::New("asf");

/**
* type:
* video/x-ms-wmv
* suffix:
* wmv
**/
const String _HttpMime::VideoXMsWmv = String::New("video/x-ms-wmv");
const String _HttpMime::SuffixWmv = String::New("wmv");

/**
* type:
* video/x-msvideo
* suffix:
* avi
**/
const String _HttpMime::VideoXMsVideo = String::New("video/x-msvideo");
const String _HttpMime::SuffixAvi = String::New("avi");


// multipart/form-data
const String _HttpMime::MultiPartFormData = String::New("multipart/form-data");
const String _HttpMime::FormData = String::New("form-data");
const String _HttpMime::Boundary = String::New("boundary");
const String _HttpMime::Binary = String::New("binary");

// x-www-form-urlencoded
const String _HttpMime::XFormUrlEncoded = String::New("application/x-www-form-urlencoded");

// CharSet
const String _HttpMime::CharSet = String::New("charset");

_HttpMime::Type _HttpMime::getTypeId() const {
    return mTypeId;
}

String _HttpMime::getType() const {
    return mType;
}

String _HttpMime::getType(_HttpMime::Type type) const {

#define CASE_SWITCH(X, Y)       \
    case st(HttpMime)::Type::Y:       \
        return st(HttpMime)::X;

    switch (type) {
        CASE_SWITCH(TextHtml,TextHtml)
        CASE_SWITCH(TextCss,TextCss)
        CASE_SWITCH(TextXml,TextXml)
        CASE_SWITCH(ImageGif,ImageGif)
        CASE_SWITCH(ImageJpeg,ImageJpeg)
        CASE_SWITCH(ApplicationJs,ApplicationJs)
        CASE_SWITCH(ApplicationAtomXml,ApplicationAtomXml)
        CASE_SWITCH(ApplicationRss,ApplicationRss)
        CASE_SWITCH(TextMathml,TextMathml)
        CASE_SWITCH(TextPlain,TextPlain)
        CASE_SWITCH(TextVndSunJ2meAppDes,TextVndSunJ2meAppDes)
        CASE_SWITCH(TextVndWapWml,TextVndWapWml)
        CASE_SWITCH(TextXComponent,TextXComponent)
        CASE_SWITCH(ImagePng,ImagePng)
        CASE_SWITCH(ImageSvgXml,ImageSvgXml)
        CASE_SWITCH(ImageTiff,ImageTiff)
        CASE_SWITCH(ImageVndWapWbmp,ImageVndWapWbmp)
        CASE_SWITCH(ImageWebp,ImageWebp)
        CASE_SWITCH(ImageXIcon,ImageXIcon)
        CASE_SWITCH(ImageXJng,ImageXJng)
        CASE_SWITCH(ImageXMsBmp,ImageXMsBmp)
        CASE_SWITCH(ApplicationFontWoff,ApplicationFontWoff)
        CASE_SWITCH(ApplicationJavaArchive,ApplicationJavaArchive)
        CASE_SWITCH(ApplicationJson,ApplicationJson)
        CASE_SWITCH(ApplicationMaxBinhex40,ApplicationMaxBinhex40)
        CASE_SWITCH(ApplicationMsword,ApplicationMsword)
        CASE_SWITCH(ApplicationPdf,ApplicationPdf)
        CASE_SWITCH(ApplicationPostScript,ApplicationPostScript)
        CASE_SWITCH(ApplicationRtf,ApplicationRtf)
        CASE_SWITCH(ApplicationVndAppleMpegurl,ApplicationVndAppleMpegurl)
        CASE_SWITCH(ApplicationVndGoogleEarthKmlXml,
                    ApplicationVndGoogleEarthKmlXml)
        CASE_SWITCH(ApplicationVndGoogleEarthKmz,
                    ApplicationVndGoogleEarthKmz)
        CASE_SWITCH(ApplicationVndMsExcel,ApplicationVndMsExcel)
        CASE_SWITCH(ApplicationVndMsFontObject,ApplicationVndMsFontObject)
        CASE_SWITCH(ApplicationVndMsPpt,ApplicationVndMsPpt)
        CASE_SWITCH(ApplicationVndOasisOpendocGraphics,
                    ApplicationVndOasisOpendocGraphics)
        CASE_SWITCH(ApplicationVndOasisOpendocPresentation,
                    ApplicationVndOasisOpendocPresentation)
        CASE_SWITCH(ApplicationVndOasisOpendocSpreadsheet,
                    ApplicationVndOasisOpendocSpreadsheet)
        CASE_SWITCH(ApplicationVndOasisOpendocText,
                    ApplicationVndOasisOpendocText)
        CASE_SWITCH(ApplicationVndOpenxmlPresentation,
                    ApplicationVndOpenxmlPresentation)
        CASE_SWITCH(ApplicationVndOpenXmlSheet,ApplicationVndOpenXmlSheet)
        CASE_SWITCH(ApplicationVndOepnXmlDoc,ApplicationVndOepnXmlDoc)
        CASE_SWITCH(ApplicationVndWapWmls,ApplicationVndWapWmls)
        CASE_SWITCH(Application7z,Application7z)
        CASE_SWITCH(ApplicationXCocoa,ApplicationXCocoa)
        CASE_SWITCH(ApplicationXJavaArch,ApplicationXJavaArch)
        CASE_SWITCH(ApplicationXJavaJnlpFile,ApplicationXJavaJnlpFile)
        CASE_SWITCH(ApplicationXMakeself,ApplicationXMakeself)
        CASE_SWITCH(ApplicationXPerl,ApplicationXPerl)
        CASE_SWITCH(ApplicationXPilot,ApplicationXPilot)
        CASE_SWITCH(ApplicationXRarCompressed,ApplicationXRarCompressed)
        CASE_SWITCH(ApplicationXReadhatPkgManager,
                    ApplicationXReadhatPkgManager)
        CASE_SWITCH(ApplicationXSea,ApplicationXSea)
        CASE_SWITCH(ApplicationXShockwaveFlash,ApplicationXShockwaveFlash)
        CASE_SWITCH(ApplicationXStuffit,ApplicationXStuffit)
        CASE_SWITCH(ApplicationXTcl,ApplicationXTcl)
        CASE_SWITCH(ApplicationXX509CaCert,ApplicationXX509CaCert)
        CASE_SWITCH(ApplicationXXpinstall,ApplicationXXpinstall)
        CASE_SWITCH(ApplicationXhtmlXml,ApplicationXhtmlXml)
        CASE_SWITCH(ApplicationXspfXml,ApplicationXspfXml)
        CASE_SWITCH(ApplicationZip,ApplicationZip)
        CASE_SWITCH(ApplicationOctetStream,ApplicationOctetStream)
        CASE_SWITCH(AudioMidi,AudioMidi)
        CASE_SWITCH(AudioMpeg,AudioMpeg)
        CASE_SWITCH(AudioOgg,AudioOgg)
        CASE_SWITCH(AudioXM4a,AudioXM4a)
        CASE_SWITCH(AudioXRealAudio,AudioXRealAudio)
        CASE_SWITCH(Video3Gpp,Video3Gpp)
        CASE_SWITCH(VideoMp2t,VideoMp2t)
        CASE_SWITCH(VideoMp4,VideoMp4)
        CASE_SWITCH(VideoMpeg,VideoMpeg)
        CASE_SWITCH(VidoQuicktime,VidoQuicktime)
        CASE_SWITCH(VideoWebm,VideoWebm)
        CASE_SWITCH(VideoXflv,VideoXflv)
        CASE_SWITCH(VideoXM4v,VideoXM4v)
        CASE_SWITCH(VideoXMng,VideoXMng)
        CASE_SWITCH(VideoXMsAsf,VideoXMsAsf)
        CASE_SWITCH(VideoXMsWmv,VideoXMsWmv)
        CASE_SWITCH(VideoXMsVideo,VideoXMsVideo)
        CASE_SWITCH(MultiPartFormData,MultiPartFormData)
        CASE_SWITCH(XFormUrlEncoded,XFormUrlEncoded)
    }

#undef CASE_SWITCH
    return nullptr;
}


sp<_HttpMime> _HttpMime::setSuffix(String suffix) {
    if(auto id = suffixToId->get(suffix);id != nullptr) {
        mTypeId = static_cast<_HttpMime::Type>(id->toValue());
        mType = getType(mTypeId);
    }
    return AutoClone(this);
}

sp<_HttpMime> _HttpMime::setType(String type) {
    this->mType = type;
    if(auto id = nameToId->get(type);id != nullptr) {
        mTypeId = static_cast<_HttpMime::Type>(id->toValue());
    }

    return AutoClone(this);
}

sp<_HttpMime> _HttpMime::setTypeId(_HttpMime::Type id) {
    this->mTypeId = id;
    mType = getType(id);
    return AutoClone(this);
}

_HttpMime::_HttpMime() {
    static std::once_flag flag;
    std::call_once(flag, []() {
        nameToId = HashMap<String,Integer>::New();
        suffixToId = HashMap<String,Integer>::New();

    #define ADD_NODE(X, Y) \
        suffixToId->put(st(HttpMime)::X,\
                        Integer::New(static_cast<int>(st(HttpMime)::Type::Y)))

        ADD_NODE(SuffixHtml,TextHtml);
        ADD_NODE(SuffixHtm,TextHtml);
        ADD_NODE(SuffixShtml,TextHtml);
        ADD_NODE(SuffixCss,TextCss);
        ADD_NODE(SuffixXml,TextXml);
        ADD_NODE(SuffixGif,ImageGif);
        ADD_NODE(SuffixJpeg,ImageJpeg);
        ADD_NODE(SuffixJpg,ImageJpeg);
        ADD_NODE(SuffixJs,ApplicationJs);
        ADD_NODE(SuffixAtom,ApplicationAtomXml);
        ADD_NODE(SuffixRss,ApplicationRss);
        ADD_NODE(SuffixMml,TextMathml);
        ADD_NODE(SuffixTxt,TextPlain);
        ADD_NODE(SuffixJad,TextVndSunJ2meAppDes);
        ADD_NODE(SuffixWml,TextVndWapWml);
        ADD_NODE(SuffixHtc,TextXComponent);
        ADD_NODE(SuffixPng,ImagePng);
        ADD_NODE(SuffixSvg,ImageSvgXml);
        ADD_NODE(SuffixSvgz,ImageSvgXml);
        ADD_NODE(SuffixTif,ImageTiff);
        ADD_NODE(SuffixTiff,ImageTiff);
        ADD_NODE(SuffixWbmp,ImageVndWapWbmp);
        ADD_NODE(SuffixWebp,ImageWebp);
        ADD_NODE(SuffixIco,ImageXIcon);
        ADD_NODE(SuffixJng,ImageXJng);
        ADD_NODE(SuffixBmp,ImageXMsBmp);
        ADD_NODE(SuffixWoff,ApplicationFontWoff);
        ADD_NODE(SuffixJar,ApplicationJavaArchive);
        ADD_NODE(SuffixWar,ApplicationJavaArchive);
        ADD_NODE(SuffixEar,ApplicationJavaArchive);
        ADD_NODE(SuffixJson,ApplicationJson);
        ADD_NODE(SuffixHqx,ApplicationMaxBinhex40);
        ADD_NODE(SuffixDoc,ApplicationMsword);
        ADD_NODE(SuffixPdf,ApplicationPdf);
        ADD_NODE(SuffixAi,ApplicationPostScript);
        ADD_NODE(SuffixEps,ApplicationPostScript);
        ADD_NODE(SuffixPs,ApplicationPostScript);
        ADD_NODE(SuffixRtf,ApplicationRtf);
        ADD_NODE(SuffixM3u8,ApplicationVndAppleMpegurl);
        ADD_NODE(SuffixKml,ApplicationVndGoogleEarthKmlXml);
        ADD_NODE(SuffixKmz,ApplicationVndGoogleEarthKmz);
        ADD_NODE(SuffixXls,ApplicationVndMsExcel);
        ADD_NODE(SuffixEot,ApplicationVndMsFontObject);
        ADD_NODE(SuffixPpt,ApplicationVndMsPpt);
        ADD_NODE(SuffixOdj,ApplicationVndOasisOpendocGraphics);
        ADD_NODE(SuffixOdp,ApplicationVndOasisOpendocPresentation);
        ADD_NODE(SuffixOds,ApplicationVndOasisOpendocSpreadsheet);
        ADD_NODE(SuffixOdt,ApplicationVndOasisOpendocText);
        ADD_NODE(SuffixPptx,ApplicationVndOpenxmlPresentation);
        ADD_NODE(SuffixXlsx,ApplicationVndOpenXmlSheet);
        ADD_NODE(SuffixDocx,ApplicationVndOepnXmlDoc);
        ADD_NODE(SuffixWmlc,ApplicationVndWapWmls);
        ADD_NODE(Suffix7z,Application7z);
        ADD_NODE(SuffixCco,ApplicationXCocoa);
        ADD_NODE(SuffixJardiff,ApplicationXJavaArch);
        ADD_NODE(SuffixJnlp,ApplicationXJavaJnlpFile);
        ADD_NODE(SuffixRun,ApplicationXMakeself);
        ADD_NODE(SuffixPl,ApplicationXPerl);
        ADD_NODE(SuffixPm,ApplicationXPerl);
        ADD_NODE(SuffixPrc,ApplicationXPilot);
        ADD_NODE(SuffixPdb,ApplicationXPilot);
        ADD_NODE(SuffixRar,ApplicationXRarCompressed);
        ADD_NODE(SuffixRpm,ApplicationXReadhatPkgManager);
        ADD_NODE(SuffixSea,ApplicationXSea);
        ADD_NODE(SuffixSwf,ApplicationXShockwaveFlash);
        ADD_NODE(SuffixSit,ApplicationXStuffit);
        ADD_NODE(SuffixTk,ApplicationXTcl);
        ADD_NODE(SuffixTcl,ApplicationXTcl);
        ADD_NODE(SuffixDer,ApplicationXX509CaCert);
        ADD_NODE(SuffixPem,ApplicationXX509CaCert);
        ADD_NODE(SuffixCrt,ApplicationXX509CaCert);
        ADD_NODE(SuffixXpi,ApplicationXXpinstall);
        ADD_NODE(SuffixXhtml,ApplicationXhtmlXml);
        ADD_NODE(SuffixXspf,ApplicationXspfXml);
        ADD_NODE(SuffixZip,ApplicationZip);
        ADD_NODE(SuffixBin,ApplicationOctetStream);
        ADD_NODE(SuffixExe,ApplicationOctetStream);
        ADD_NODE(SuffixDll,ApplicationOctetStream);
        ADD_NODE(SuffixDeb,ApplicationOctetStream);
        ADD_NODE(SuffixDmg,ApplicationOctetStream);
        ADD_NODE(SuffixIso,ApplicationOctetStream);
        ADD_NODE(SuffixImg,ApplicationOctetStream);
        ADD_NODE(SuffixMsi,ApplicationOctetStream);
        ADD_NODE(SuffixMsp,ApplicationOctetStream);
        ADD_NODE(SuffixMsm,ApplicationOctetStream);
        ADD_NODE(SuffixMid,AudioMidi);
        ADD_NODE(SuffixMidi,AudioMidi);
        ADD_NODE(SuffixKar,AudioMidi);
        ADD_NODE(SuffixMp3,AudioMpeg);
        ADD_NODE(SuffixOgg,AudioOgg);
        ADD_NODE(SuffixM4a,AudioXM4a);
        ADD_NODE(SuffixRa,AudioXRealAudio);
        ADD_NODE(Suffix3Gpp,Video3Gpp);
        ADD_NODE(Sufix3Gp,Video3Gpp);
        ADD_NODE(SuffixTs,VideoMp2t);
        ADD_NODE(SuffixMp4,VideoMp4);
        ADD_NODE(SuffixMpeg,VideoMpeg);
        ADD_NODE(SuffixMpg,VideoMpeg);
        ADD_NODE(SuffixMov,VidoQuicktime);
        ADD_NODE(SuffixWebm,VideoWebm);
        ADD_NODE(SuffixFlv,VideoXflv);
        ADD_NODE(SuffixM4V,VideoXM4v);
        ADD_NODE(SuffixMng,VideoXMng);
        ADD_NODE(SuffixAsx,VideoXMsAsf);
        ADD_NODE(SuffixAsf,VideoXMsAsf);
        ADD_NODE(SuffixWmv,VideoXMsWmv);
        ADD_NODE(SuffixAvi,VideoXMsVideo);
    #undef ADD_NODE

    #define ADD_NODE(X, Y)                                                         \
        nameToId->put(st(HttpMime)::X,\
            Integer::New(static_cast<int>(st(HttpMime)::Type::Y)))

        ADD_NODE(TextHtml,TextHtml);
        ADD_NODE(TextCss,TextCss);
        ADD_NODE(TextXml,TextXml);
        ADD_NODE(ImageGif,ImageGif);
        ADD_NODE(ImageJpeg,ImageJpeg);
        ADD_NODE(ApplicationJs,ApplicationJs);
        ADD_NODE(ApplicationAtomXml,ApplicationAtomXml);
        ADD_NODE(ApplicationRss,ApplicationRss);
        ADD_NODE(TextMathml,TextMathml);
        ADD_NODE(TextPlain,TextPlain);
        ADD_NODE(TextVndSunJ2meAppDes,TextVndSunJ2meAppDes);
        ADD_NODE(TextVndWapWml,TextVndWapWml);
        ADD_NODE(TextXComponent,TextXComponent);
        ADD_NODE(ImagePng,ImagePng);
        ADD_NODE(ImageSvgXml,ImageSvgXml);
        ADD_NODE(ImageTiff,ImageTiff);
        ADD_NODE(ImageVndWapWbmp,ImageVndWapWbmp);
        ADD_NODE(ImageWebp,ImageWebp);
        ADD_NODE(ImageXIcon,ImageXIcon);
        ADD_NODE(ImageXJng,ImageXJng);
        ADD_NODE(ImageXMsBmp,ImageXMsBmp);
        ADD_NODE(ApplicationFontWoff,ApplicationFontWoff);
        ADD_NODE(ApplicationJavaArchive,ApplicationJavaArchive);
        ADD_NODE(ApplicationJson,ApplicationJson);
        ADD_NODE(ApplicationMaxBinhex40,ApplicationMaxBinhex40);
        ADD_NODE(ApplicationMsword,ApplicationMsword);
        ADD_NODE(ApplicationPdf,ApplicationPdf);
        ADD_NODE(ApplicationPostScript,ApplicationPostScript);
        ADD_NODE(ApplicationRtf,ApplicationRtf);
        ADD_NODE(ApplicationVndAppleMpegurl,ApplicationVndAppleMpegurl);
        ADD_NODE(ApplicationVndGoogleEarthKmlXml,
                ApplicationVndGoogleEarthKmlXml);
        ADD_NODE(ApplicationVndGoogleEarthKmz,ApplicationVndGoogleEarthKmz);
        ADD_NODE(ApplicationVndMsExcel,ApplicationVndMsExcel);
        ADD_NODE(ApplicationVndMsFontObject,ApplicationVndMsFontObject);
        ADD_NODE(ApplicationVndMsPpt,ApplicationVndMsPpt);
        ADD_NODE(ApplicationVndOasisOpendocGraphics,
                ApplicationVndOasisOpendocGraphics);
        ADD_NODE(ApplicationVndOasisOpendocPresentation,
                ApplicationVndOasisOpendocPresentation);
        ADD_NODE(ApplicationVndOasisOpendocSpreadsheet,
                ApplicationVndOasisOpendocSpreadsheet);
        ADD_NODE(ApplicationVndOasisOpendocText,
                ApplicationVndOasisOpendocText);
        ADD_NODE(ApplicationVndOpenxmlPresentation,
                ApplicationVndOpenxmlPresentation);
        ADD_NODE(ApplicationVndOpenXmlSheet,ApplicationVndOpenXmlSheet);
        ADD_NODE(ApplicationVndOepnXmlDoc,ApplicationVndOepnXmlDoc);
        ADD_NODE(ApplicationVndWapWmls,ApplicationVndWapWmls);
        ADD_NODE(Application7z,Application7z);
        ADD_NODE(ApplicationXCocoa,ApplicationXCocoa);
        ADD_NODE(ApplicationXJavaArch,ApplicationXJavaArch);
        ADD_NODE(ApplicationXJavaJnlpFile,ApplicationXJavaJnlpFile);
        ADD_NODE(ApplicationXMakeself,ApplicationXMakeself);
        ADD_NODE(ApplicationXPerl,ApplicationXPerl);
        ADD_NODE(ApplicationXPilot,ApplicationXPilot);
        ADD_NODE(ApplicationXRarCompressed,ApplicationXRarCompressed);
        ADD_NODE(ApplicationXReadhatPkgManager,ApplicationXReadhatPkgManager);
        ADD_NODE(ApplicationXSea,ApplicationXSea);
        ADD_NODE(ApplicationXShockwaveFlash,ApplicationXShockwaveFlash);
        ADD_NODE(ApplicationXStuffit,ApplicationXStuffit);
        ADD_NODE(ApplicationXTcl,ApplicationXTcl);
        ADD_NODE(ApplicationXX509CaCert,ApplicationXX509CaCert);
        ADD_NODE(ApplicationXXpinstall,ApplicationXXpinstall);
        ADD_NODE(ApplicationXhtmlXml,ApplicationXhtmlXml);
        ADD_NODE(ApplicationXspfXml,ApplicationXspfXml);
        ADD_NODE(ApplicationZip,ApplicationZip);
        ADD_NODE(ApplicationOctetStream,ApplicationOctetStream);
        ADD_NODE(AudioMidi,AudioMidi);
        ADD_NODE(AudioMpeg,AudioMpeg);
        ADD_NODE(AudioOgg,AudioOgg);
        ADD_NODE(AudioXM4a,AudioXM4a);
        ADD_NODE(AudioXRealAudio,AudioXRealAudio);
        ADD_NODE(Video3Gpp,Video3Gpp);
        ADD_NODE(VideoMp2t,VideoMp2t);
        ADD_NODE(VideoMp4,VideoMp4);
        ADD_NODE(VideoMpeg,VideoMpeg);
        ADD_NODE(VidoQuicktime,VidoQuicktime);
        ADD_NODE(VideoWebm,VideoWebm);
        ADD_NODE(VideoXflv,VideoXflv);
        ADD_NODE(VideoXM4v,VideoXM4v);
        ADD_NODE(VideoXMng,VideoXMng);
        ADD_NODE(VideoXMsAsf,VideoXMsAsf);
        ADD_NODE(VideoXMsWmv,VideoXMsWmv);
        ADD_NODE(VideoXMsVideo,VideoXMsVideo);
        ADD_NODE(MultiPartFormData,MultiPartFormData);
        ADD_NODE(XFormUrlEncoded,XFormUrlEncoded);
    #undef ADD_NODE
    }); 
}

} // namespace obotcha
