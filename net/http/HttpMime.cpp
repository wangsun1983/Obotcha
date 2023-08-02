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

int _HttpMime::getId() const {
    return mId;
}

String _HttpMime::getType() const {
    return mType;
}

String _HttpMime::getType(int type) const {

#define CASE_SWITCH(X, Y)       \
    case st(HttpMime)::Y:       \
        return st(HttpMime)::X;

    switch (type) {
        CASE_SWITCH(TextHtml, TypeTextHtml)
        CASE_SWITCH(TextCss, TypeTextCss)
        CASE_SWITCH(TextXml, TypeTextXml)
        CASE_SWITCH(ImageGif, TypeImageGif)
        CASE_SWITCH(ImageJpeg, TypeImageJpeg)
        CASE_SWITCH(ApplicationJs, TypeApplicationJs)
        CASE_SWITCH(ApplicationAtomXml, TypeApplicationAtomXml)
        CASE_SWITCH(ApplicationRss, TypeApplicationRss)
        CASE_SWITCH(TextMathml, TypeTextMathml)
        CASE_SWITCH(TextPlain, TypeTextPlain)
        CASE_SWITCH(TextVndSunJ2meAppDes, TypeTextVndSunJ2meAppDes)
        CASE_SWITCH(TextVndWapWml, TypeTextVndWapWml)
        CASE_SWITCH(TextXComponent, TypeTextXComponent)
        CASE_SWITCH(ImagePng, TypeImagePng)
        CASE_SWITCH(ImageSvgXml, TypeImageSvgXml)
        CASE_SWITCH(ImageTiff, TypeImageTiff);
        CASE_SWITCH(ImageVndWapWbmp, TypeImageVndWapWbmp)
        CASE_SWITCH(ImageWebp, TypeImageWebp)
        CASE_SWITCH(ImageXIcon, TypeImageXIcon)
        CASE_SWITCH(ImageXJng, TypeImageXJng)
        CASE_SWITCH(ImageXMsBmp, TypeImageXMsBmp)
        CASE_SWITCH(ApplicationFontWoff, TypeApplicationFontWoff)
        CASE_SWITCH(ApplicationJavaArchive, TypeApplicationJavaArchive)
        CASE_SWITCH(ApplicationJson, TypeApplicationJson)
        CASE_SWITCH(ApplicationMaxBinhex40, TypeApplicationMaxBinhex40)
        CASE_SWITCH(ApplicationMsword, TypeApplicationMsword)
        CASE_SWITCH(ApplicationPdf, TypeApplicationPdf)
        CASE_SWITCH(ApplicationPostScript, TypeApplicationPostScript);
        CASE_SWITCH(ApplicationRtf, TypeApplicationRtf)
        CASE_SWITCH(ApplicationVndAppleMpegurl, TypeApplicationVndAppleMpegurl)
        CASE_SWITCH(ApplicationVndGoogleEarthKmlXml,
                    TypeApplicationVndGoogleEarthKmlXml)
        CASE_SWITCH(ApplicationVndGoogleEarthKmz,
                    TypeApplicationVndGoogleEarthKmz)
        CASE_SWITCH(ApplicationVndMsExcel, TypeApplicationVndMsExcel)
        CASE_SWITCH(ApplicationVndMsFontObject, TypeApplicationVndMsFontObject)
        CASE_SWITCH(ApplicationVndMsPpt, TypeApplicationVndMsPpt)
        CASE_SWITCH(ApplicationVndOasisOpendocGraphics,
                    TypeApplicationVndOasisOpendocGraphics)
        CASE_SWITCH(ApplicationVndOasisOpendocPresentation,
                    TypeApplicationVndOasisOpendocPresentation)
        CASE_SWITCH(ApplicationVndOasisOpendocSpreadsheet,
                    TypeApplicationVndOasisOpendocSpreadsheet)
        CASE_SWITCH(ApplicationVndOasisOpendocText,
                    TypeApplicationVndOasisOpendocText)
        CASE_SWITCH(ApplicationVndOpenxmlPresentation,
                    TypeApplicationVndOpenxmlPresentation)
        CASE_SWITCH(ApplicationVndOpenXmlSheet, TypeApplicationVndOpenXmlSheet)
        CASE_SWITCH(ApplicationVndOepnXmlDoc, TypeApplicationVndOepnXmlDoc)
        CASE_SWITCH(ApplicationVndWapWmls, TypeApplicationVndWapWmls)
        CASE_SWITCH(Application7z, TypeApplication7z)
        CASE_SWITCH(ApplicationXCocoa, TypeApplicationXCocoa)
        CASE_SWITCH(ApplicationXJavaArch, TypeApplicationXJavaArch)
        CASE_SWITCH(ApplicationXJavaJnlpFile, TypeApplicationXJavaJnlpFile)
        CASE_SWITCH(ApplicationXMakeself, TypeApplicationXMakeself)
        CASE_SWITCH(ApplicationXPerl, TypeApplicationXPerl)
        CASE_SWITCH(ApplicationXPilot, TypeApplicationXPilot)
        CASE_SWITCH(ApplicationXRarCompressed, TypeApplicationXRarCompressed)
        CASE_SWITCH(ApplicationXReadhatPkgManager,
                    TypeApplicationXReadhatPkgManager)
        CASE_SWITCH(ApplicationXSea, TypeApplicationXSea)
        CASE_SWITCH(ApplicationXShockwaveFlash, TypeApplicationXShockwaveFlash)
        CASE_SWITCH(ApplicationXStuffit, TypeApplicationXStuffit)
        CASE_SWITCH(ApplicationXTcl, TypeApplicationXTcl)
        CASE_SWITCH(ApplicationXX509CaCert, TypeApplicationXX509CaCert)
        CASE_SWITCH(ApplicationXXpinstall, TypeApplicationXXpinstall)
        CASE_SWITCH(ApplicationXhtmlXml, TypeApplicationXhtmlXml)
        CASE_SWITCH(ApplicationXspfXml, TypeApplicationXspfXml)
        CASE_SWITCH(ApplicationZip, TypeApplicationZip)
        CASE_SWITCH(ApplicationOctetStream, TypeApplicationOctetStream)
        CASE_SWITCH(AudioMidi, TypeAudioMidi)
        CASE_SWITCH(AudioMpeg, TypeAudioMpeg)
        CASE_SWITCH(AudioOgg, TypeAudioOgg)
        CASE_SWITCH(AudioXM4a, TypeAudioXM4a)
        CASE_SWITCH(AudioXRealAudio, TypeAudioXRealAudio)
        CASE_SWITCH(Video3Gpp, TypeVideo3Gpp)
        CASE_SWITCH(VideoMp2t, TypeVideoMp2t)
        CASE_SWITCH(VideoMp4, TypeVideoMp4)
        CASE_SWITCH(VideoMpeg, TypeVideoMpeg)
        CASE_SWITCH(VidoQuicktime, TypeVidoQuicktime)
        CASE_SWITCH(VideoWebm, TypeVideoWebm)
        CASE_SWITCH(VideoXflv, TypeVideoXflv)
        CASE_SWITCH(VideoXM4v, TypeVideoXM4v)
        CASE_SWITCH(VideoXMng, TypeVideoXMng)
        CASE_SWITCH(VideoXMsAsf, TypeVideoXMsAsf)
        CASE_SWITCH(VideoXMsWmv, TypeVideoXMsWmv)
        CASE_SWITCH(VideoXMsVideo, TypeVideoXMsVideo)
        CASE_SWITCH(MultiPartFormData, TypeMultiPartFormData)
        CASE_SWITCH(XFormUrlEncoded, TypeXFormUrlEncoded)
    }

#undef CASE_SWITCH
    return nullptr;
}


sp<_HttpMime> _HttpMime::setSuffix(String suffix) {
    Integer v = suffixToId->get(suffix);
    if(v != nullptr) {
        mId = v->toValue();
        mType = getType(mId);
    }
    return AutoClone(this);
}

sp<_HttpMime> _HttpMime::setType(String type) {
    this->mType = type;
    Integer v = nameToId->get(type);
    if(v != nullptr) {
        mId = v->toValue();
    }

    return AutoClone(this);
}

sp<_HttpMime> _HttpMime::setId(int id) {
    this->mId = id;
    mType = getType(id);
    return AutoClone(this);
}

_HttpMime::_HttpMime() {
    static std::once_flag flag;
    std::call_once(flag, []() {
        nameToId = createHashMap<String,Integer>();
        suffixToId = createHashMap<String,Integer>();

    #define ADD_NODE(X, Y) \
        suffixToId->put(st(HttpMime)::X,createInteger(st(HttpMime)::Y))

        ADD_NODE(SuffixHtml, TypeTextHtml);
        ADD_NODE(SuffixHtm, TypeTextHtml);
        ADD_NODE(SuffixShtml, TypeTextHtml);
        ADD_NODE(SuffixCss, TypeTextCss);
        ADD_NODE(SuffixXml, TypeTextXml);
        ADD_NODE(SuffixGif, TypeImageGif);
        ADD_NODE(SuffixJpeg, TypeImageJpeg);
        ADD_NODE(SuffixJpg, TypeImageJpeg);
        ADD_NODE(SuffixJs, TypeApplicationJs);
        ADD_NODE(SuffixAtom, TypeApplicationAtomXml);
        ADD_NODE(SuffixRss, TypeApplicationRss);
        ADD_NODE(SuffixMml, TypeTextMathml);
        ADD_NODE(SuffixTxt, TypeTextPlain);
        ADD_NODE(SuffixJad, TypeTextVndSunJ2meAppDes);
        ADD_NODE(SuffixWml, TypeTextVndWapWml);
        ADD_NODE(SuffixHtc, TypeTextXComponent);
        ADD_NODE(SuffixPng, TypeImagePng);
        ADD_NODE(SuffixSvg, TypeImageSvgXml);
        ADD_NODE(SuffixSvgz, TypeImageSvgXml);
        ADD_NODE(SuffixTif, TypeImageTiff);
        ADD_NODE(SuffixTiff, TypeImageTiff);
        ADD_NODE(SuffixWbmp, TypeImageVndWapWbmp);
        ADD_NODE(SuffixWebp, TypeImageWebp);
        ADD_NODE(SuffixIco, TypeImageXIcon);
        ADD_NODE(SuffixJng, TypeImageXJng);
        ADD_NODE(SuffixBmp, TypeImageXMsBmp);
        ADD_NODE(SuffixWoff, TypeApplicationFontWoff);
        ADD_NODE(SuffixJar, TypeApplicationJavaArchive);
        ADD_NODE(SuffixWar, TypeApplicationJavaArchive);
        ADD_NODE(SuffixEar, TypeApplicationJavaArchive);
        ADD_NODE(SuffixJson, TypeApplicationJson);
        ADD_NODE(SuffixHqx, TypeApplicationMaxBinhex40);
        ADD_NODE(SuffixDoc, TypeApplicationMsword);
        ADD_NODE(SuffixPdf, TypeApplicationPdf);
        ADD_NODE(SuffixAi, TypeApplicationPostScript);
        ADD_NODE(SuffixEps, TypeApplicationPostScript);
        ADD_NODE(SuffixPs, TypeApplicationPostScript);
        ADD_NODE(SuffixRtf, TypeApplicationRtf);
        ADD_NODE(SuffixM3u8, TypeApplicationVndAppleMpegurl);
        ADD_NODE(SuffixKml, TypeApplicationVndGoogleEarthKmlXml);
        ADD_NODE(SuffixKmz, TypeApplicationVndGoogleEarthKmz);
        ADD_NODE(SuffixXls, TypeApplicationVndMsExcel);
        ADD_NODE(SuffixEot, TypeApplicationVndMsFontObject);
        ADD_NODE(SuffixPpt, TypeApplicationVndMsPpt);
        ADD_NODE(SuffixOdj, TypeApplicationVndOasisOpendocGraphics);
        ADD_NODE(SuffixOdp, TypeApplicationVndOasisOpendocPresentation);
        ADD_NODE(SuffixOds, TypeApplicationVndOasisOpendocSpreadsheet);
        ADD_NODE(SuffixOdt, TypeApplicationVndOasisOpendocText);
        ADD_NODE(SuffixPptx, TypeApplicationVndOpenxmlPresentation);
        ADD_NODE(SuffixXlsx, TypeApplicationVndOpenXmlSheet);
        ADD_NODE(SuffixDocx, TypeApplicationVndOepnXmlDoc);
        ADD_NODE(SuffixWmlc, TypeApplicationVndWapWmls);
        ADD_NODE(Suffix7z, TypeApplication7z);
        ADD_NODE(SuffixCco, TypeApplicationXCocoa);
        ADD_NODE(SuffixJardiff, TypeApplicationXJavaArch);
        ADD_NODE(SuffixJnlp, TypeApplicationXJavaJnlpFile);
        ADD_NODE(SuffixRun, TypeApplicationXMakeself);
        ADD_NODE(SuffixPl, TypeApplicationXPerl);
        ADD_NODE(SuffixPm, TypeApplicationXPerl);
        ADD_NODE(SuffixPrc, TypeApplicationXPilot);
        ADD_NODE(SuffixPdb, TypeApplicationXPilot);
        ADD_NODE(SuffixRar, TypeApplicationXRarCompressed);
        ADD_NODE(SuffixRpm, TypeApplicationXReadhatPkgManager);
        ADD_NODE(SuffixSea, TypeApplicationXSea);
        ADD_NODE(SuffixSwf, TypeApplicationXShockwaveFlash);
        ADD_NODE(SuffixSit, TypeApplicationXStuffit);
        ADD_NODE(SuffixTk, TypeApplicationXTcl);
        ADD_NODE(SuffixTcl, TypeApplicationXTcl);
        ADD_NODE(SuffixDer, TypeApplicationXX509CaCert);
        ADD_NODE(SuffixPem, TypeApplicationXX509CaCert);
        ADD_NODE(SuffixCrt, TypeApplicationXX509CaCert);
        ADD_NODE(SuffixXpi, TypeApplicationXXpinstall);
        ADD_NODE(SuffixXhtml, TypeApplicationXhtmlXml);
        ADD_NODE(SuffixXspf, TypeApplicationXspfXml);
        ADD_NODE(SuffixZip, TypeApplicationZip);
        ADD_NODE(SuffixBin, TypeApplicationOctetStream);
        ADD_NODE(SuffixExe, TypeApplicationOctetStream);
        ADD_NODE(SuffixDll, TypeApplicationOctetStream);
        ADD_NODE(SuffixDeb, TypeApplicationOctetStream);
        ADD_NODE(SuffixDmg, TypeApplicationOctetStream);
        ADD_NODE(SuffixIso, TypeApplicationOctetStream);
        ADD_NODE(SuffixImg, TypeApplicationOctetStream);
        ADD_NODE(SuffixMsi, TypeApplicationOctetStream);
        ADD_NODE(SuffixMsp, TypeApplicationOctetStream);
        ADD_NODE(SuffixMsm, TypeApplicationOctetStream);
        ADD_NODE(SuffixMid, TypeAudioMidi);
        ADD_NODE(SuffixMidi, TypeAudioMidi);
        ADD_NODE(SuffixKar, TypeAudioMidi);
        ADD_NODE(SuffixMp3, TypeAudioMpeg);
        ADD_NODE(SuffixOgg, TypeAudioOgg);
        ADD_NODE(SuffixM4a, TypeAudioXM4a);
        ADD_NODE(SuffixRa, TypeAudioXRealAudio);
        ADD_NODE(Suffix3Gpp, TypeVideo3Gpp);
        ADD_NODE(Sufix3Gp, TypeVideo3Gpp);
        ADD_NODE(SuffixTs, TypeVideoMp2t);
        ADD_NODE(SuffixMp4, TypeVideoMp4);
        ADD_NODE(SuffixMpeg, TypeVideoMpeg);
        ADD_NODE(SuffixMpg, TypeVideoMpeg);
        ADD_NODE(SuffixMov, TypeVidoQuicktime);
        ADD_NODE(SuffixWebm, TypeVideoWebm);
        ADD_NODE(SuffixFlv, TypeVideoXflv);
        ADD_NODE(SuffixM4V, TypeVideoXM4v);
        ADD_NODE(SuffixMng, TypeVideoXMng);
        ADD_NODE(SuffixAsx, TypeVideoXMsAsf);
        ADD_NODE(SuffixAsf, TypeVideoXMsAsf);
        ADD_NODE(SuffixWmv, TypeVideoXMsWmv);
        ADD_NODE(SuffixAvi, TypeVideoXMsVideo);
    #undef ADD_NODE

    #define ADD_NODE(X, Y)                                                         \
        nameToId->put(st(HttpMime)::X,createInteger(st(HttpMime)::Y))

        ADD_NODE(TextHtml, TypeTextHtml);
        ADD_NODE(TextCss, TypeTextCss);
        ADD_NODE(TextXml, TypeTextXml);
        ADD_NODE(ImageGif, TypeImageGif);
        ADD_NODE(ImageJpeg, TypeImageJpeg);
        ADD_NODE(ApplicationJs, TypeApplicationJs);
        ADD_NODE(ApplicationAtomXml, TypeApplicationAtomXml);
        ADD_NODE(ApplicationRss, TypeApplicationRss);
        ADD_NODE(TextMathml, TypeTextMathml);
        ADD_NODE(TextPlain, TypeTextPlain);
        ADD_NODE(TextVndSunJ2meAppDes, TypeTextVndSunJ2meAppDes);
        ADD_NODE(TextVndWapWml, TypeTextVndWapWml);
        ADD_NODE(TextXComponent, TypeTextXComponent);
        ADD_NODE(ImagePng, TypeImagePng);
        ADD_NODE(ImageSvgXml, TypeImageSvgXml);
        ADD_NODE(ImageTiff, TypeImageTiff);
        ADD_NODE(ImageVndWapWbmp, TypeImageVndWapWbmp);
        ADD_NODE(ImageWebp, TypeImageWebp);
        ADD_NODE(ImageXIcon, TypeImageXIcon);
        ADD_NODE(ImageXJng, TypeImageXJng);
        ADD_NODE(ImageXMsBmp, TypeImageXMsBmp);
        ADD_NODE(ApplicationFontWoff, TypeApplicationFontWoff);
        ADD_NODE(ApplicationJavaArchive, TypeApplicationJavaArchive);
        ADD_NODE(ApplicationJson, TypeApplicationJson);
        ADD_NODE(ApplicationMaxBinhex40, TypeApplicationMaxBinhex40);
        ADD_NODE(ApplicationMsword, TypeApplicationMsword);
        ADD_NODE(ApplicationPdf, TypeApplicationPdf);
        ADD_NODE(ApplicationPostScript, TypeApplicationPostScript);
        ADD_NODE(ApplicationRtf, TypeApplicationRtf);
        ADD_NODE(ApplicationVndAppleMpegurl, TypeApplicationVndAppleMpegurl);
        ADD_NODE(ApplicationVndGoogleEarthKmlXml,
                TypeApplicationVndGoogleEarthKmlXml);
        ADD_NODE(ApplicationVndGoogleEarthKmz, TypeApplicationVndGoogleEarthKmz);
        ADD_NODE(ApplicationVndMsExcel, TypeApplicationVndMsExcel);
        ADD_NODE(ApplicationVndMsFontObject, TypeApplicationVndMsFontObject);
        ADD_NODE(ApplicationVndMsPpt, TypeApplicationVndMsPpt);
        ADD_NODE(ApplicationVndOasisOpendocGraphics,
                TypeApplicationVndOasisOpendocGraphics);
        ADD_NODE(ApplicationVndOasisOpendocPresentation,
                TypeApplicationVndOasisOpendocPresentation);
        ADD_NODE(ApplicationVndOasisOpendocSpreadsheet,
                TypeApplicationVndOasisOpendocSpreadsheet);
        ADD_NODE(ApplicationVndOasisOpendocText,
                TypeApplicationVndOasisOpendocText);
        ADD_NODE(ApplicationVndOpenxmlPresentation,
                TypeApplicationVndOpenxmlPresentation);
        ADD_NODE(ApplicationVndOpenXmlSheet, TypeApplicationVndOpenXmlSheet);
        ADD_NODE(ApplicationVndOepnXmlDoc, TypeApplicationVndOepnXmlDoc);
        ADD_NODE(ApplicationVndWapWmls, TypeApplicationVndWapWmls);
        ADD_NODE(Application7z, TypeApplication7z);
        ADD_NODE(ApplicationXCocoa, TypeApplicationXCocoa);
        ADD_NODE(ApplicationXJavaArch, TypeApplicationXJavaArch);
        ADD_NODE(ApplicationXJavaJnlpFile, TypeApplicationXJavaJnlpFile);
        ADD_NODE(ApplicationXMakeself, TypeApplicationXMakeself);
        ADD_NODE(ApplicationXPerl, TypeApplicationXPerl);
        ADD_NODE(ApplicationXPilot, TypeApplicationXPilot);
        ADD_NODE(ApplicationXRarCompressed, TypeApplicationXRarCompressed);
        ADD_NODE(ApplicationXReadhatPkgManager, TypeApplicationXReadhatPkgManager);
        ADD_NODE(ApplicationXSea, TypeApplicationXSea);
        ADD_NODE(ApplicationXShockwaveFlash, TypeApplicationXShockwaveFlash);
        ADD_NODE(ApplicationXStuffit, TypeApplicationXStuffit);
        ADD_NODE(ApplicationXTcl, TypeApplicationXTcl);
        ADD_NODE(ApplicationXX509CaCert, TypeApplicationXX509CaCert);
        ADD_NODE(ApplicationXXpinstall, TypeApplicationXXpinstall);
        ADD_NODE(ApplicationXhtmlXml, TypeApplicationXhtmlXml);
        ADD_NODE(ApplicationXspfXml, TypeApplicationXspfXml);
        ADD_NODE(ApplicationZip, TypeApplicationZip);
        ADD_NODE(ApplicationOctetStream, TypeApplicationOctetStream);
        ADD_NODE(AudioMidi, TypeAudioMidi);
        ADD_NODE(AudioMpeg, TypeAudioMpeg);
        ADD_NODE(AudioOgg, TypeAudioOgg);
        ADD_NODE(AudioXM4a, TypeAudioXM4a);
        ADD_NODE(AudioXRealAudio, TypeAudioXRealAudio);
        ADD_NODE(Video3Gpp, TypeVideo3Gpp);
        ADD_NODE(VideoMp2t, TypeVideoMp2t);
        ADD_NODE(VideoMp4, TypeVideoMp4);
        ADD_NODE(VideoMpeg, TypeVideoMpeg);
        ADD_NODE(VidoQuicktime, TypeVidoQuicktime);
        ADD_NODE(VideoWebm, TypeVideoWebm);
        ADD_NODE(VideoXflv, TypeVideoXflv);
        ADD_NODE(VideoXM4v, TypeVideoXM4v);
        ADD_NODE(VideoXMng, TypeVideoXMng);
        ADD_NODE(VideoXMsAsf, TypeVideoXMsAsf);
        ADD_NODE(VideoXMsWmv, TypeVideoXMsWmv);
        ADD_NODE(VideoXMsVideo, TypeVideoXMsVideo);
        ADD_NODE(MultiPartFormData, TypeMultiPartFormData);
        ADD_NODE(XFormUrlEncoded, TypeXFormUrlEncoded);
    #undef ADD_NODE
    }); 
}

} // namespace obotcha
