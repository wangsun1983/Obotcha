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
const String _HttpMime::TextHtml = createString("text/html");
const String _HttpMime::SuffixHtml = createString("html");
const String _HttpMime::SuffixHtm = createString("htm");
const String _HttpMime::SuffixShtml = createString("shtml");

/**
* type:
* text/css
* suffix:
* css
**/ 
const String _HttpMime::TextCss = createString("text/css");
const String _HttpMime::SuffixCss = createString("css");

/**
* type:
* text/xml
* suffix:
* xml
**/ 
const String _HttpMime::TextXml = createString("text/xml");
const String _HttpMime::SuffixXml = createString("xml");

/**
* type:
* image/gif
* suffix:
* gif
**/ 
const String _HttpMime::ImageGif = createString("image/gif");
const String _HttpMime::SuffixGif = createString("gif");

/**
* type:
* image/jpeg
* suffix:
* jpeg or jpg
**/ 
const String _HttpMime::ImageJpeg = createString("image/jpeg");
const String _HttpMime::SuffixJpeg = createString("jpeg");
const String _HttpMime::SuffixJpg = createString("jpg");

/**
* type:
* application/javascript
* suffix:
* js
**/
const String _HttpMime::ApplicationJs = createString("application/javascript");
const String _HttpMime::SuffixJs = createString("js");

/**
* type:
* application/atom+xml
* suffix:
* atom
**/
const String _HttpMime::ApplicationAtomXml = createString("application/atom+xml");
const String _HttpMime::SuffixAtom = createString("atom");

/**
* type:
* application/rss+xml
* suffix:
* rss
**/
const String _HttpMime::ApplicationRss = createString("application/rss+xml");
const String _HttpMime::SuffixRss = createString("rss");

/**
* type:
* text/mathml
* suffix:
* mml
**/
const String _HttpMime::TextMathml = createString("text/mathml");
const String _HttpMime::SuffixMml = createString("mml");

/**
* type:
* text/plain
* suffix:
* txt
**/
const String _HttpMime::TextPlain = createString("text/plain");
const String _HttpMime::SuffixTxt = createString("txt");

/**
* type:
* text/vnd.sun.j2me.app-descriptor
* suffix:
* jad
**/
const String _HttpMime::TextVndSunJ2meAppDes = createString("text/vnd.sun.j2me.app-descriptor");
const String _HttpMime::SuffixJad = createString("jad");

/**
* type:
* text/vnd.wap.wml
* suffix:
* wml
**/
const String _HttpMime::TextVndWapWml = createString("text/vnd.wap.wml");
const String _HttpMime::SuffixWml = createString("wml");

/**
* type:
* text/x-component
* suffix:
* htc
**/
const String _HttpMime::TextXComponent = createString("text/x-component");
const String _HttpMime::SuffixHtc = createString("htc");

/**
* type:
* image/png
* suffix:
* png
**/
const String _HttpMime::ImagePng = createString("image/png");
const String _HttpMime::SuffixPng = createString("png");

/**
* type:
* image/svg+xml
* suffix:
* svg or svgz
**/
const String _HttpMime::ImageSvgXml = createString("image/svg+xml");
const String _HttpMime::SuffixSvg = createString("svg");
const String _HttpMime::SuffixSvgz = createString("svgz");

/**
* type:
* image/tiff
* suffix:
* tif or tiff
**/
const String _HttpMime::ImageTiff = createString("image/tiff");
const String _HttpMime::SuffixTif = createString("tif");
const String _HttpMime::SuffixTiff = createString("tiff");

/**
* type:
* image/vnd.wap.wbmp
* suffix:
* wbmp
**/
const String _HttpMime::ImageVndWapWbmp = createString("image/vnd.wap.wbmp");
const String _HttpMime::SuffixWbmp = createString("wbmp");

/**
* type:
* image/webp
* suffix:
* webp
**/
const String _HttpMime::ImageWebp = createString("image/webp");
const String _HttpMime::SuffixWebp = createString("webp");

/**
* type:
* image/x-icon
* suffix:
* ico
**/
const String _HttpMime::ImageXIcon = createString("image/x-icon");
const String _HttpMime::SuffixIco = createString("ico");

/**
* type:
* image/x-jng
* suffix:
* jng
**/
const String _HttpMime::ImageXJng = createString("image/x-jng");
const String _HttpMime::SuffixJng = createString("jng");

/**
* type:
* image/x-ms-bmp
* suffix:
* bmp
**/
const String _HttpMime::ImageXMsBmp = createString("image/x-ms-bmp");
const String _HttpMime::SuffixBmp = createString("bmp");

/**
* type:
* application/font-woff
* suffix:
* woff
**/
const String _HttpMime::ApplicationFontWoff = createString("application/font-woff");
const String _HttpMime::SuffixWoff = createString("woff");

/**
* type:
* application/java-archive
* suffix:
* jar or war or ear
**/
const String _HttpMime::ApplicationJavaArchive = createString("application/java-archive");
const String _HttpMime::SuffixJar = createString("jar");
const String _HttpMime::SuffixWar = createString("war");
const String _HttpMime::SuffixEar = createString("ear");

/**
* type:
* application/json
* suffix:
* json
**/
const String _HttpMime::ApplicationJson = createString("application/json");
const String _HttpMime::SuffixJson = createString("json");

/**
* type:
* application/mac-binhex40
* suffix:
* hqx
**/
const String _HttpMime::ApplicationMaxBinhex40 = createString("application/mac-binhex40");
const String _HttpMime::SuffixHqx = createString("hqx");

/**
* type:
* application/msword
* suffix:
* doc
**/
const String _HttpMime::ApplicationMsword = createString("application/msword");
const String _HttpMime::SuffixDoc = createString("doc");

/**
* type:
* application/pdf
* suffix:
* pdf
**/
const String _HttpMime::ApplicationPdf = createString("application/pdf");
const String _HttpMime::SuffixPdf = createString("pdf");

/**
* type:
* application/postscript
* suffix:
* ps or eps or ai
**/
const String _HttpMime::ApplicationPostScript = createString("application/postscript");
const String _HttpMime::SuffixPs = createString("ps");
const String _HttpMime::SuffixEps = createString("eps");
const String _HttpMime::SuffixAi = createString("ai");

/**
* type:
* application/rtf
* suffix:
* rtf
**/
const String _HttpMime::ApplicationRtf = createString("application/rtf");
const String _HttpMime::SuffixRtf = createString("rtf");

/**
* type:
* application/vnd.apple.mpegurl
* suffix:
* m3u8
**/
const String _HttpMime::ApplicationVndAppleMpegurl = createString("application/vnd.apple.mpegurl");
const String _HttpMime::SuffixM3u8 = createString("m3u8");

/**
* type:
* application/vnd.google-earth.kml+xml
* suffix:
* kml
**/
const String _HttpMime::ApplicationVndGoogleEarthKmlXml = createString("application/vnd.google-earth.kml+xml");
const String _HttpMime::SuffixKml = createString("kml");

/**
* type:
* application/vnd.google-earth.kmz
* suffix:
* kmz
**/
const String _HttpMime::ApplicationVndGoogleEarthKmz = createString("application/vnd.google-earth.kmz");
const String _HttpMime::SuffixKmz = createString("kmz");

/**
* type:
* application/vnd.ms-excel
* suffix:
* xls
**/
const String _HttpMime::ApplicationVndMsExcel = createString("application/vnd.ms-excel");
const String _HttpMime::SuffixXls = createString("xls");

/**
* type:
* application/vnd.ms-fontobject
* suffix:
* eot
**/
const String _HttpMime::ApplicationVndMsFontObject = createString("application/vnd.ms-fontobject");
const String _HttpMime::SuffixEot = createString("eot");

/**
* type:
* application/vnd.ms-powerpoint
* suffix:
* ppt
**/
const String _HttpMime::ApplicationVndMsPpt = createString("application/vnd.ms-powerpoint");
const String _HttpMime::SuffixPpt = createString("ppt");

/**
* type:
* application/vnd.oasis.opendocument.graphics
* suffix:
* odg
**/
const String _HttpMime::ApplicationVndOasisOpendocGraphics = createString("application/vnd.oasis.opendocument.graphics");
const String _HttpMime::SuffixOdj = createString("odg");

/**
* type:
* application/vnd.oasis.opendocument.presentation
* suffix:
* odp
**/
const String _HttpMime::ApplicationVndOasisOpendocPresentation = createString("application/vnd.oasis.opendocument.presentation");
const String _HttpMime::SuffixOdp = createString("odp");

/**
* type:
* application/vnd.oasis.opendocument.spreadsheet
* suffix:
* ods
**/
const String _HttpMime::ApplicationVndOasisOpendocSpreadsheet = createString("application/vnd.oasis.opendocument.spreadsheet");
const String _HttpMime::SuffixOds = createString("ods");

/**
* type:
* application/vnd.oasis.opendocument.text
* suffix:
* odt
**/
const String _HttpMime::ApplicationVndOasisOpendocText = createString("application/vnd.oasis.opendocument.text");
const String _HttpMime::SuffixOdt = createString("odt");

/**
* type:
* application/vnd.openxmlformats-officedocument.presentationml.presentation
* suffix:
* pptx
**/
const String _HttpMime::ApplicationVndOpenxmlPresentation = createString(
    "application/vnd.openxmlformats-officedocument.presentationml.presentation");
const String _HttpMime::SuffixPptx = createString("pptx");

/**
* type:
* application/vnd.openxmlformats-officedocument.spreadsheetml.sheet
* suffix:
* xlsx
**/
const String _HttpMime::ApplicationVndOpenXmlSheet = createString(
    "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
const String _HttpMime::SuffixXlsx = createString("xlsx");

/**
* type:
* application/vnd.openxmlformats-officedocument.wordprocessingml.document
* suffix:
* docx
**/
const String _HttpMime::ApplicationVndOepnXmlDoc = createString(
    "application/vnd.openxmlformats-officedocument.wordprocessingml.document");
const String _HttpMime::SuffixDocx = createString("docx");

/**
* type:
* application/vnd.wap.wmlc 
* suffix:
* wmlc
**/
const String _HttpMime::ApplicationVndWapWmls = createString("application/vnd.wap.wmlc");
const String _HttpMime::SuffixWmlc = createString("wmlc");

/**
* type:
* application/x-7z-compressed
* suffix:
* 7z
**/
const String _HttpMime::Application7z = createString("application/x-7z-compressed");
const String _HttpMime::Suffix7z = createString("7z");

/**
* type:
* application/x-cocoa
* suffix:
* cco
**/
const String _HttpMime::ApplicationXCocoa = createString("application/x-cocoa");
const String _HttpMime::SuffixCco = createString("cco");

/**
* type:
* application/x-java-archive-diff
* suffix:
* jardiff
**/
const String _HttpMime::ApplicationXJavaArch = createString("application/x-java-archive-diff");
const String _HttpMime::SuffixJardiff = createString("jardiff");

/**
* type:
* application/x-java-jnlp-file
* suffix:
* jnlp
**/
const String _HttpMime::ApplicationXJavaJnlpFile = createString("application/x-java-jnlp-file");
const String _HttpMime::SuffixJnlp = createString("jnlp");

/**
* type:
* application/x-makeself
* suffix:
* run
**/
const String _HttpMime::ApplicationXMakeself = createString("application/x-makeself");
const String _HttpMime::SuffixRun = createString("run");

/**
* type:
* application/x-perl
* suffix:
* pl or pm
**/
const String _HttpMime::ApplicationXPerl = createString("application/x-perl");
const String _HttpMime::SuffixPl = createString("pl");
const String _HttpMime::SuffixPm = createString("pm");

/**
* type:
* application/x-pilot
* suffix:
* prc or pdb
**/
const String _HttpMime::ApplicationXPilot = createString("application/x-pilot");
const String _HttpMime::SuffixPrc = createString("prc");
const String _HttpMime::SuffixPdb = createString("pdb");

/**
* type:
* application/x-rar-compressed
* suffix:
* rar
**/
const String _HttpMime::ApplicationXRarCompressed = createString("application/x-rar-compressed");
const String _HttpMime::SuffixRar = createString("rar");

/**
* type:
* application/x-redhat-package-manager
* suffix:
* rpm
**/
const String _HttpMime::ApplicationXReadhatPkgManager = createString("application/x-redhat-package-manager");
const String _HttpMime::SuffixRpm = createString("rpm");

/**
* type:
* application/x-sea
* suffix:
* sea
**/
const String _HttpMime::ApplicationXSea = createString("application/x-sea");
const String _HttpMime::SuffixSea = createString("sea");

/**
* type:
* application/x-shockwave-flash
* suffix:
* swf
**/
const String _HttpMime::ApplicationXShockwaveFlash = createString("application/x-shockwave-flash");
const String _HttpMime::SuffixSwf = createString("swf");

/**
* type:
* application/x-stuffit
* suffix:
* sit
**/
const String _HttpMime::ApplicationXStuffit = createString("application/x-stuffit");
const String _HttpMime::SuffixSit = createString("sit");

/**
* type:
* application/x-tcl
* suffix:
* tcl or tk
**/
const String _HttpMime::ApplicationXTcl = createString("application/x-tcl");
const String _HttpMime::SuffixTcl = createString("tcl");
const String _HttpMime::SuffixTk = createString("tk");

/**
* type:
* application/x-x509-ca-cert
* suffix:
* der or pem or crt
**/
const String _HttpMime::ApplicationXX509CaCert = createString("application/x-x509-ca-cert");
const String _HttpMime::SuffixDer = createString("der");
const String _HttpMime::SuffixPem = createString("pem");
const String _HttpMime::SuffixCrt = createString("crt");

/**
* type:
* application/x-xpinstall
* suffix:
* xpi
**/
const String _HttpMime::ApplicationXXpinstall = createString("application/x-xpinstall");
const String _HttpMime::SuffixXpi = createString("xpi");

/**
* type:
* application/xhtml+xml
* suffix:
* xhtml
**/
const String _HttpMime::ApplicationXhtmlXml = createString("application/xhtml+xml");
const String _HttpMime::SuffixXhtml = createString("xhtml");

/**
* type:
* application/xspf+xml 
* suffix:
* xspf
**/
const String _HttpMime::ApplicationXspfXml = createString("application/xspf+xml");
const String _HttpMime::SuffixXspf = createString("xspf");

/**
* type:
* application/zip
* suffix:
* zip
**/
const String _HttpMime::ApplicationZip = createString("application/zip");
const String _HttpMime::SuffixZip = createString("zip");

/**
* type:
* application/octet-stream
* suffix:
* bin exe dll deb dmg iso img msi msp msm
**/
const String _HttpMime::ApplicationOctetStream = createString("application/octet-stream");
const String _HttpMime::SuffixBin = createString("bin");
const String _HttpMime::SuffixExe = createString("exe");
const String _HttpMime::SuffixDll = createString("dll");
const String _HttpMime::SuffixDeb = createString("deb");
const String _HttpMime::SuffixDmg = createString("dmg");
const String _HttpMime::SuffixIso = createString("iso");
const String _HttpMime::SuffixImg = createString("img");
const String _HttpMime::SuffixMsi = createString("msi");
const String _HttpMime::SuffixMsp = createString("msp");
const String _HttpMime::SuffixMsm = createString("msm");

/**
* type:
* audio/midi
* suffix:
* mid or midi or kar
**/
const String _HttpMime::AudioMidi = createString("audio/midi");
const String _HttpMime::SuffixMid = createString("mid");
const String _HttpMime::SuffixMidi = createString("midi");
const String _HttpMime::SuffixKar = createString("kar");

/**
* type:
* audio/mpeg
* suffix:
* mp3
**/
const String _HttpMime::AudioMpeg = createString("audio/mpeg");
const String _HttpMime::SuffixMp3 = createString("mp3");

/**
* type:
* audio/ogg
* suffix:
* ogg
**/
const String _HttpMime::AudioOgg = createString("audio/ogg");
const String _HttpMime::SuffixOgg = createString("ogg");

/**
* type:
* audio/x-m4a
* suffix:
* m4a
**/
const String _HttpMime::AudioXM4a = createString("audio/x-m4a");
const String _HttpMime::SuffixM4a = createString("m4a");

/**
* type:
* audio/x-realaudio   
* suffix:
* ra
**/
const String _HttpMime::AudioXRealAudio = createString("audio/x-realaudio");
const String _HttpMime::SuffixRa = createString("ra");

/**
* type:
* video/3gpp
* suffix:
* 3gpp or 3gp
**/
const String _HttpMime::Video3Gpp = createString("video/3gpp");
const String _HttpMime::Suffix3Gpp = createString("3gpp");
const String _HttpMime::Sufix3Gp = createString("3gp");

/**
* type:
* video/mp2t
* suffix:
* ts
**/
const String _HttpMime::VideoMp2t = createString("video/mp2t");
const String _HttpMime::SuffixTs = createString("ts");

/**
* type:
* video/mp4
* suffix:
* mp4
**/
const String _HttpMime::VideoMp4 = createString("video/mp4");
const String _HttpMime::SuffixMp4 = createString("mp4");

/**
* type:
* video/mpeg
* suffix:
* mpeg or mpg
**/
const String _HttpMime::VideoMpeg = createString("video/mpeg");
const String _HttpMime::SuffixMpeg = createString("mpeg");
const String _HttpMime::SuffixMpg = createString("mpg");

/**
* type:
* video/quicktime
* suffix:
* mov
**/
const String _HttpMime::VidoQuicktime = createString("video/quicktime");
const String _HttpMime::SuffixMov = createString("mov");

/**
* type:
* video/webm 
* suffix:
* webm
**/
const String _HttpMime::VideoWebm = createString("video/webm");
const String _HttpMime::SuffixWebm = createString("webm");

/**
* type:
* video/x-flv
* suffix:
* flv
**/
const String _HttpMime::VideoXflv = createString("video/x-flv");
const String _HttpMime::SuffixFlv = createString("flv");

/**
* type:
* video/x-m4v
* suffix:
* m4v
**/
const String _HttpMime::VideoXM4v = createString("video/x-m4v");
const String _HttpMime::SuffixM4V = createString("m4v");

/**
* type:
* video/x-mng
* suffix:
* mng
**/
const String _HttpMime::VideoXMng = createString("video/x-mng");
const String _HttpMime::SuffixMng = createString("mng");

/**
* type:
* video/x-ms-asf
* suffix:
* asx or asf
**/
const String _HttpMime::VideoXMsAsf = createString("video/x-ms-asf");
const String _HttpMime::SuffixAsx = createString("asx");
const String _HttpMime::SuffixAsf = createString("asf");

/**
* type:
* video/x-ms-wmv
* suffix:
* wmv
**/
const String _HttpMime::VideoXMsWmv = createString("video/x-ms-wmv");
const String _HttpMime::SuffixWmv = createString("wmv");

/**
* type:
* video/x-msvideo
* suffix:
* avi
**/
const String _HttpMime::VideoXMsVideo = createString("video/x-msvideo");
const String _HttpMime::SuffixAvi = createString("avi");


// multipart/form-data
const String _HttpMime::MultiPartFormData = createString("multipart/form-data");
const String _HttpMime::FormData = createString("form-data");
const String _HttpMime::Boundary = createString("boundary");

// x-www-form-urlencoded
const String _HttpMime::XFormUrlEncoded = createString("application/x-www-form-urlencoded");

// CharSet
const String _HttpMime::CharSet = createString("charset");

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
        nameToId = createHashMap<String,Integer>();
        suffixToId = createHashMap<String,Integer>();

    #define ADD_NODE(X, Y) \
        suffixToId->put(st(HttpMime)::X,\
                        createInteger(static_cast<int>(st(HttpMime)::Type::Y)))

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
            createInteger(static_cast<int>(st(HttpMime)::Type::Y)))

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
