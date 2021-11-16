// according nginx/conf/mime.types

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "AutoLock.hpp"
#include "ByteArray.hpp"
#include "File.hpp"
#include "HttpMime.hpp"
#include "HttpCookie.hpp"
#include "Mutex.hpp"
#include "String.hpp"

namespace obotcha {

FileTypeSearchNode *_HttpMime::mSuffixRootNode = nullptr;
FileTypeSearchNode *_HttpMime::mContentTypeNode = nullptr;

// text/html(html htm shtml)
const String _HttpMime::TextHtml =
    createString("text/html"); // text/html(html htm shtml)
const String _HttpMime::SuffixHtml = createString("html");
const String _HttpMime::SuffixHtm = createString("htm");
const String _HttpMime::SuffixShtml = createString("shtml");

// text/css(css)
const String _HttpMime::TextCss = createString("text/css");
const String _HttpMime::SuffixCss = createString("css");

// text/xml(xml)
const String _HttpMime::TextXml = createString("text/xml");
const String _HttpMime::SuffixXml = createString("xml");

// image/gif(gif)
const String _HttpMime::ImageGif = createString("image/gif");
const String _HttpMime::SuffixGif = createString("gif");

// image/jpeg(jpeg jpg)
const String _HttpMime::ImageJpeg = createString("image/jpeg");
const String _HttpMime::SuffixJpeg = createString("jpeg");
const String _HttpMime::SuffixJpg = createString("jpg");

// application/javascript(js)
const String _HttpMime::ApplicationJs =
    createString("application/javascript");
const String _HttpMime::SuffixJs = createString("js");

// application/atom+xml(atom)
const String _HttpMime::ApplicationAtomXml =
    createString("application/atom+xml");
const String _HttpMime::SuffixAtom = createString("atom");

// application/rss+xml(rss)
const String _HttpMime::ApplicationRss =
    createString("application/rss+xml");
const String _HttpMime::SuffixRss = createString("rss");

// text/mathml(mml)
const String _HttpMime::TextMathml = createString("text/mathml");
const String _HttpMime::SuffixMml = createString("mml");

// text/plain(txt)
const String _HttpMime::TextPlain = createString("text/plain");
const String _HttpMime::SuffixTxt = createString("txt");

// text/vnd.sun.j2me.app-descriptor(jad)
const String _HttpMime::TextVndSunJ2meAppDes =
    createString("text/vnd.sun.j2me.app-descriptor");
const String _HttpMime::SuffixJad = createString("jad");

// text/vnd.wap.wml                                 wml;
const String _HttpMime::TextVndWapWml = createString("text/vnd.wap.wml");
const String _HttpMime::SuffixWml = createString("wml");

// text/x-component                                 htc;
const String _HttpMime::TextXComponent =
    createString("text/x-component");
const String _HttpMime::SuffixHtc = createString("htc");

// image/png      png;
const String _HttpMime::ImagePng = createString("image/png");
const String _HttpMime::SuffixPng = createString("png");

// image/svg+xml     svg svgz;
const String _HttpMime::ImageSvgXml = createString("image/svg+xml");
const String _HttpMime::SuffixSvg = createString("svg");
const String _HttpMime::SuffixSvgz = createString("svgz");

// image/tiff     tif tiff;
const String _HttpMime::ImageTiff = createString("image/tiff");
const String _HttpMime::SuffixTif = createString("tif");
const String _HttpMime::SuffixTiff = createString("tiff");

// image/vnd.wap.wbmp                               wbmp;
const String _HttpMime::ImageVndWapWbmp =
    createString("image/vnd.wap.wbmp");
const String _HttpMime::SuffixWbmp = createString("wbmp");

// image/webp     webp;
const String _HttpMime::ImageWebp = createString("image/webp");
const String _HttpMime::SuffixWebp = createString("webp");

// image/x-icon      ico;
const String _HttpMime::ImageXIcon = createString("image/x-icon");
const String _HttpMime::SuffixIco = createString("ico");

// image/x-jng    jng;
const String _HttpMime::ImageXJng = createString("image/x-jng");
const String _HttpMime::SuffixJng = createString("jng");

// image/x-ms-bmp    bmp;
const String _HttpMime::ImageXMsBmp = createString("image/x-ms-bmp");
const String _HttpMime::SuffixBmp = createString("bmp");

// application/font-woff                            woff;
const String _HttpMime::ApplicationFontWoff =
    createString("application/font-woff");
const String _HttpMime::SuffixWoff = createString("woff");

// application/java-archive                         jar war ear;
const String _HttpMime::ApplicationJavaArchive =
    createString("application/java-archive");
const String _HttpMime::SuffixJar = createString("jar");
const String _HttpMime::SuffixWar = createString("war");
const String _HttpMime::SuffixEar = createString("ear");

// application/json                                 json;
const String _HttpMime::ApplicationJson =
    createString("application/json");
const String _HttpMime::SuffixJson = createString("json");

// application/mac-binhex40                         hqx;
const String _HttpMime::ApplicationMaxBinhex40 =
    createString("application/mac-binhex40");
const String _HttpMime::SuffixHqx = createString("hqx");

// application/msword                               doc;
const String _HttpMime::ApplicationMsword =
    createString("application/msword");
const String _HttpMime::SuffixDoc = createString("doc");

// application/pdf                                  pdf;
const String _HttpMime::ApplicationPdf = createString("application/pdf");
const String _HttpMime::SuffixPdf = createString("pdf");

// application/postscript                           ps eps ai;
const String _HttpMime::ApplicationPostScript =
    createString("application/postscript");
const String _HttpMime::SuffixPs = createString("ps");
const String _HttpMime::SuffixEps = createString("eps");
const String _HttpMime::SuffixAi = createString("ai");

// application/rtf                                  rtf;
const String _HttpMime::ApplicationRtf = createString("application/rtf");
const String _HttpMime::SuffixRtf = createString("rtf");

// application/vnd.apple.mpegurl                    m3u8;
const String _HttpMime::ApplicationVndAppleMpegurl =
    createString("application/vnd.apple.mpegurl");
const String _HttpMime::SuffixM3u8 = createString("m3u8");

// application/vnd.google-earth.kml+xml             kml;
const String _HttpMime::ApplicationVndGoogleEarthKmlXml =
    createString("application/vnd.google-earth.kml+xml");
const String _HttpMime::SuffixKml = createString("kml");

// application/vnd.google-earth.kmz                 kmz;
const String _HttpMime::ApplicationVndGoogleEarthKmz =
    createString("application/vnd.google-earth.kmz");
const String _HttpMime::SuffixKmz = createString("kmz");

// application/vnd.ms-excel                         xls;
const String _HttpMime::ApplicationVndMsExcel =
    createString("application/vnd.ms-excel");
const String _HttpMime::SuffixXls = createString("xls");

// application/vnd.ms-fontobject                    eot;
const String _HttpMime::ApplicationVndMsFontObject =
    createString("application/vnd.ms-fontobject");
const String _HttpMime::SuffixEot = createString("eot");

// application/vnd.ms-powerpoint                    ppt;
const String _HttpMime::ApplicationVndMsPpt =
    createString("application/vnd.ms-powerpoint");
const String _HttpMime::SuffixPpt = createString("ppt");

// application/vnd.oasis.opendocument.graphics      odg;
const String _HttpMime::ApplicationVndOasisOpendocGraphics =
    createString("application/vnd.oasis.opendocument.graphics");
const String _HttpMime::SuffixOdj = createString("odg");

// application/vnd.oasis.opendocument.presentation  odp;
const String _HttpMime::ApplicationVndOasisOpendocPresentation =
    createString("application/vnd.oasis.opendocument.presentation");
const String _HttpMime::SuffixOdp = createString("odp");

// application/vnd.oasis.opendocument.spreadsheet   ods;
const String _HttpMime::ApplicationVndOasisOpendocSpreadsheet =
    createString("application/vnd.oasis.opendocument.spreadsheet");
const String _HttpMime::SuffixOds = createString("ods");

// application/vnd.oasis.opendocument.text          odt;
const String _HttpMime::ApplicationVndOasisOpendocText =
    createString("application/vnd.oasis.opendocument.text");
const String _HttpMime::SuffixOdt = createString("odt");

// application/vnd.openxmlformats-officedocument.presentationml.presentation
// pptx;
const String _HttpMime::ApplicationVndOpenxmlPresentation = createString(
    "application/"
    "vnd.openxmlformats-officedocument.presentationml.presentation");
const String _HttpMime::SuffixPptx = createString("pptx");

// application/vnd.openxmlformats-officedocument.spreadsheetml.sheet
//               xlsx;
const String _HttpMime::ApplicationVndOpenXmlSheet = createString(
    "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
const String _HttpMime::SuffixXlsx = createString("xlsx");

// application/vnd.openxmlformats-officedocument.wordprocessingml.document
//               docx;
const String _HttpMime::ApplicationVndOepnXmlDoc = createString(
    "application/vnd.openxmlformats-officedocument.wordprocessingml.document");
const String _HttpMime::SuffixDocx = createString("docx");

// application/vnd.wap.wmlc                         wmlc;
const String _HttpMime::ApplicationVndWapWmls =
    createString("application/vnd.wap.wmlc");
const String _HttpMime::SuffixWmlc = createString("wmlc");

// application/x-7z-compressed                      7z;
const String _HttpMime::Application7z =
    createString("application/x-7z-compressed");
const String _HttpMime::Suffix7z = createString("7z");

// application/x-cocoa                              cco;
const String _HttpMime::ApplicationXCocoa =
    createString("application/x-cocoa");
const String _HttpMime::SuffixCco = createString("cco");

// application/x-java-archive-diff                  jardiff;
const String _HttpMime::ApplicationXJavaArch =
    createString("application/x-java-archive-diff");
const String _HttpMime::SuffixJardiff = createString("jardiff");

// application/x-java-jnlp-file                     jnlp;
const String _HttpMime::ApplicationXJavaJnlpFile =
    createString("application/x-java-jnlp-file");
const String _HttpMime::SuffixJnlp = createString("jnlp");

// application/x-makeself                           run;
const String _HttpMime::ApplicationXMakeself =
    createString("application/x-makeself");
const String _HttpMime::SuffixRun = createString("run");

// application/x-perl                               pl pm;
const String _HttpMime::ApplicationXPerl =
    createString("application/x-perl");
const String _HttpMime::SuffixPl = createString("pl");
const String _HttpMime::SuffixPm = createString("pm");

// application/x-pilot                              prc pdb;
const String _HttpMime::ApplicationXPilot =
    createString("application/x-pilot");
const String _HttpMime::SuffixPrc = createString("prc");
const String _HttpMime::SuffixPdb = createString("pdb");

// application/x-rar-compressed                     rar;
const String _HttpMime::ApplicationXRarCompressed =
    createString("application/x-rar-compressed");
const String _HttpMime::SuffixRar = createString("rar");

// application/x-redhat-package-manager             rpm;
const String _HttpMime::ApplicationXReadhatPkgManager =
    createString("application/x-redhat-package-manager");
const String _HttpMime::SuffixRpm = createString("rpm");

// application/x-sea                                sea;
const String _HttpMime::ApplicationXSea =
    createString("application/x-sea");
const String _HttpMime::SuffixSea = createString("sea");

// application/x-shockwave-flash                    swf;
const String _HttpMime::ApplicationXShockwaveFlash =
    createString("application/x-shockwave-flash");
const String _HttpMime::SuffixSwf = createString("swf");

// application/x-stuffit                            sit;
const String _HttpMime::ApplicationXStuffit =
    createString("application/x-stuffit");
const String _HttpMime::SuffixSit = createString("sit");

// application/x-tcl                                tcl tk;
const String _HttpMime::ApplicationXTcl =
    createString("application/x-tcl");
const String _HttpMime::SuffixTcl = createString("tcl");
const String _HttpMime::SuffixTk = createString("tk");

// application/x-x509-ca-cert                       der pem crt;
const String _HttpMime::ApplicationXX509CaCert =
    createString("application/x-x509-ca-cert");
const String _HttpMime::SuffixDer = createString("der");
const String _HttpMime::SuffixPem = createString("pem");
const String _HttpMime::SuffixCrt = createString("crt");

// application/x-xpinstall                          xpi;
const String _HttpMime::ApplicationXXpinstall =
    createString("application/x-xpinstall");
const String _HttpMime::SuffixXpi = createString("xpi");

// application/xhtml+xml                            xhtml;
const String _HttpMime::ApplicationXhtmlXml =
    createString("application/xhtml+xml");
const String _HttpMime::SuffixXhtml = createString("xhtml");

// application/xspf+xml                             xspf;
const String _HttpMime::ApplicationXspfXml =
    createString("application/xspf+xml");
const String _HttpMime::SuffixXspf = createString("xspf");

// application/zip                                  zip;
const String _HttpMime::ApplicationZip = createString("application/zip");
const String _HttpMime::SuffixZip = createString("zip");

// application/octet-stream                         bin exe dll;
const String _HttpMime::ApplicationOctetStream =
    createString("application/octet-stream");
const String _HttpMime::SuffixBin = createString("bin");
const String _HttpMime::SuffixExe = createString("exe");
const String _HttpMime::SuffixDll = createString("dll");

// application/octet-stream                         deb;
const String _HttpMime::SuffixDeb = createString("deb");

// application/octet-stream                         dmg;
const String _HttpMime::SuffixDmg = createString("dmg");

// application/octet-stream                         iso img;
const String _HttpMime::SuffixIso = createString("iso");
const String _HttpMime::SuffixImg = createString("img");

// application/octet-stream                         msi msp msm;
const String _HttpMime::SuffixMsi = createString("msi");
const String _HttpMime::SuffixMsp = createString("msp");
const String _HttpMime::SuffixMsm = createString("msm");

// audio/midi     mid midi kar;
const String _HttpMime::AudioMidi = createString("audio/midi");
const String _HttpMime::SuffixMid = createString("mid");
const String _HttpMime::SuffixMidi = createString("midi");
const String _HttpMime::SuffixKar = createString("kar");

// audio/mpeg     mp3;
const String _HttpMime::AudioMpeg = createString("audio/mpeg");
const String _HttpMime::SuffixMp3 = createString("mp3");

// audio/ogg      ogg;
const String _HttpMime::AudioOgg = createString("audio/ogg");
const String _HttpMime::SuffixOgg = createString("ogg");

// audio/x-m4a    m4a;
const String _HttpMime::AudioXM4a = createString("audio/x-m4a");
const String _HttpMime::SuffixM4a = createString("m4a");

// audio/x-realaudio                                ra;
const String _HttpMime::AudioXRealAudio =
    createString("audio/x-realaudio");
const String _HttpMime::SuffixRa = createString("ra");

// video/3gpp     3gpp 3gp;
const String _HttpMime::Video3Gpp = createString("video/3gpp");
const String _HttpMime::Suffix3Gpp = createString("3gpp");
const String _HttpMime::Sufix3Gp = createString("3gp");

// video/mp2t     ts;
const String _HttpMime::VideoMp2t = createString("video/mp2t");
const String _HttpMime::SuffixTs = createString("ts");

// video/mp4      mp4;
const String _HttpMime::VideoMp4 = createString("video/mp4");
const String _HttpMime::SuffixMp4 = createString("mp4");

// video/mpeg     mpeg mpg;
const String _HttpMime::VideoMpeg = createString("video/mpeg");
const String _HttpMime::SuffixMpeg = createString("mpeg");
const String _HttpMime::SuffixMpg = createString("mpg");

// video/quicktime                                  mov;
const String _HttpMime::VidoQuicktime = createString("video/quicktime");
const String _HttpMime::SuffixMov = createString("mov");

// video/webm     webm;
const String _HttpMime::VideoWebm = createString("video/webm");
const String _HttpMime::SuffixWebm = createString("webm");

// video/x-flv    flv;
const String _HttpMime::VideoXflv = createString("video/x-flv");
const String _HttpMime::SuffixFlv = createString("flv");

// video/x-m4v    m4v;
const String _HttpMime::VideoXM4v = createString("video/x-m4v");
const String _HttpMime::SuffixM4V = createString("m4v");

// video/x-mng    mng;
const String _HttpMime::VideoXMng = createString("video/x-mng");
const String _HttpMime::SuffixMng = createString("mng");

// video/x-ms-asf    asx asf;
const String _HttpMime::VideoXMsAsf = createString("video/x-ms-asf");
const String _HttpMime::SuffixAsx = createString("asx");
const String _HttpMime::SuffixAsf = createString("asf");

// video/x-ms-wmv    wmv;
const String _HttpMime::VideoXMsWmv = createString("video/x-ms-wmv");
const String _HttpMime::SuffixWmv = createString("wmv");

// video/x-msvideo                                  avi;
const String _HttpMime::VideoXMsVideo = createString("video/x-msvideo");
const String _HttpMime::SuffixAvi = createString("avi");

// multipart/form-data
const String _HttpMime::MultiPartFormData = createString("multipart/form-data");
const String _HttpMime::FormData = createString("form-data");
const String _HttpMime::Boundary = createString("boundary");

// x-www-form-urlencoded
const String _HttpMime::XFormUrlEncoded =
    createString("application/x-www-form-urlencoded");

// CharSet
const String _HttpMime::CharSet = createString("charset");

void _HttpMime::setTypeName(String v) {
    String s = v->toLowerCase();
    mType = searchNode(mContentTypeNode, s->toChars(), s->size());
}

void _HttpMime::setTypeId(int id) {
    mType = id;
}

void _HttpMime::setSuffix(String v) {
    String s = v->toLowerCase();
    mType = searchNode(mSuffixRootNode, s->toChars(), s->size());
}

int _HttpMime::getTypeId() {
    return mType;
}

String _HttpMime::getTypeName() {

#define CASE_SWITCH(X, Y)                                                      \
    case st(HttpMime)::Y:                                               \
        return st(HttpMime)::X;

    switch (mType) {
        CASE_SWITCH(TextHtml, TypeTextHtml);
        CASE_SWITCH(TextCss, TypeTextCss);
        CASE_SWITCH(TextXml, TypeTextXml);
        CASE_SWITCH(ImageGif, TypeImageGif);
        CASE_SWITCH(ImageJpeg, TypeImageJpeg);
        CASE_SWITCH(ApplicationJs, TypeApplicationJs);
        CASE_SWITCH(ApplicationAtomXml, TypeApplicationAtomXml);
        CASE_SWITCH(ApplicationRss, TypeApplicationRss);
        CASE_SWITCH(TextMathml, TypeTextMathml);
        CASE_SWITCH(TextPlain, TypeTextPlain);
        CASE_SWITCH(TextVndSunJ2meAppDes, TypeTextVndSunJ2meAppDes);
        CASE_SWITCH(TextVndWapWml, TypeTextVndWapWml);
        CASE_SWITCH(TextXComponent, TypeTextXComponent);
        CASE_SWITCH(ImagePng, TypeImagePng);
        CASE_SWITCH(ImageSvgXml, TypeImageSvgXml);
        CASE_SWITCH(ImageTiff, TypeImageTiff);
        CASE_SWITCH(ImageVndWapWbmp, TypeImageVndWapWbmp);
        CASE_SWITCH(ImageWebp, TypeImageWebp);
        CASE_SWITCH(ImageXIcon, TypeImageXIcon);
        CASE_SWITCH(ImageXJng, TypeImageXJng);
        CASE_SWITCH(ImageXMsBmp, TypeImageXMsBmp);
        CASE_SWITCH(ApplicationFontWoff, TypeApplicationFontWoff);
        CASE_SWITCH(ApplicationJavaArchive, TypeApplicationJavaArchive);
        CASE_SWITCH(ApplicationJson, TypeApplicationJson);
        CASE_SWITCH(ApplicationMaxBinhex40, TypeApplicationMaxBinhex40);
        CASE_SWITCH(ApplicationMsword, TypeApplicationMsword);
        CASE_SWITCH(ApplicationPdf, TypeApplicationPdf);
        CASE_SWITCH(ApplicationPostScript, TypeApplicationPostScript);
        CASE_SWITCH(ApplicationRtf, TypeApplicationRtf);
        CASE_SWITCH(ApplicationVndAppleMpegurl, TypeApplicationVndAppleMpegurl);
        CASE_SWITCH(ApplicationVndGoogleEarthKmlXml,
                    TypeApplicationVndGoogleEarthKmlXml);
        CASE_SWITCH(ApplicationVndGoogleEarthKmz,
                    TypeApplicationVndGoogleEarthKmz);
        CASE_SWITCH(ApplicationVndMsExcel, TypeApplicationVndMsExcel);
        CASE_SWITCH(ApplicationVndMsFontObject, TypeApplicationVndMsFontObject);
        CASE_SWITCH(ApplicationVndMsPpt, TypeApplicationVndMsPpt);
        CASE_SWITCH(ApplicationVndOasisOpendocGraphics,
                    TypeApplicationVndOasisOpendocGraphics);
        CASE_SWITCH(ApplicationVndOasisOpendocPresentation,
                    TypeApplicationVndOasisOpendocPresentation);
        CASE_SWITCH(ApplicationVndOasisOpendocSpreadsheet,
                    TypeApplicationVndOasisOpendocSpreadsheet);
        CASE_SWITCH(ApplicationVndOasisOpendocText,
                    TypeApplicationVndOasisOpendocText);
        CASE_SWITCH(ApplicationVndOpenxmlPresentation,
                    TypeApplicationVndOpenxmlPresentation);
        CASE_SWITCH(ApplicationVndOpenXmlSheet, TypeApplicationVndOpenXmlSheet);
        CASE_SWITCH(ApplicationVndOepnXmlDoc, TypeApplicationVndOepnXmlDoc);
        CASE_SWITCH(ApplicationVndWapWmls, TypeApplicationVndWapWmls);
        CASE_SWITCH(Application7z, TypeApplication7z);
        CASE_SWITCH(ApplicationXCocoa, TypeApplicationXCocoa);
        CASE_SWITCH(ApplicationXJavaArch, TypeApplicationXJavaArch);
        CASE_SWITCH(ApplicationXJavaJnlpFile, TypeApplicationXJavaJnlpFile);
        CASE_SWITCH(ApplicationXMakeself, TypeApplicationXMakeself);
        CASE_SWITCH(ApplicationXPerl, TypeApplicationXPerl);
        CASE_SWITCH(ApplicationXPilot, TypeApplicationXPilot);
        CASE_SWITCH(ApplicationXRarCompressed, TypeApplicationXRarCompressed);
        CASE_SWITCH(ApplicationXReadhatPkgManager,
                    TypeApplicationXReadhatPkgManager);
        CASE_SWITCH(ApplicationXSea, TypeApplicationXSea);
        CASE_SWITCH(ApplicationXShockwaveFlash, TypeApplicationXShockwaveFlash);
        CASE_SWITCH(ApplicationXStuffit, TypeApplicationXStuffit);
        CASE_SWITCH(ApplicationXTcl, TypeApplicationXTcl);
        CASE_SWITCH(ApplicationXX509CaCert, TypeApplicationXX509CaCert);
        CASE_SWITCH(ApplicationXXpinstall, TypeApplicationXXpinstall);
        CASE_SWITCH(ApplicationXhtmlXml, TypeApplicationXhtmlXml);
        CASE_SWITCH(ApplicationXspfXml, TypeApplicationXspfXml);
        CASE_SWITCH(ApplicationZip, TypeApplicationZip);
        CASE_SWITCH(ApplicationOctetStream, TypeApplicationOctetStream);
        CASE_SWITCH(AudioMidi, TypeAudioMidi);
        CASE_SWITCH(AudioMpeg, TypeAudioMpeg);
        CASE_SWITCH(AudioOgg, TypeAudioOgg);
        CASE_SWITCH(AudioXM4a, TypeAudioXM4a);
        CASE_SWITCH(AudioXRealAudio, TypeAudioXRealAudio);
        CASE_SWITCH(Video3Gpp, TypeVideo3Gpp);
        CASE_SWITCH(VideoMp2t, TypeVideoMp2t);
        CASE_SWITCH(VideoMp4, TypeVideoMp4);
        CASE_SWITCH(VideoMpeg, TypeVideoMpeg);
        CASE_SWITCH(VidoQuicktime, TypeVidoQuicktime);
        CASE_SWITCH(VideoWebm, TypeVideoWebm);
        CASE_SWITCH(VideoXflv, TypeVideoXflv);
        CASE_SWITCH(VideoXM4v, TypeVideoXM4v);
        CASE_SWITCH(VideoXMng, TypeVideoXMng);
        CASE_SWITCH(VideoXMsAsf, TypeVideoXMsAsf);
        CASE_SWITCH(VideoXMsWmv, TypeVideoXMsWmv);
        CASE_SWITCH(VideoXMsVideo, TypeVideoXMsVideo);
        CASE_SWITCH(MultiPartFormData, TypeMultiPartFormData);
        CASE_SWITCH(XFormUrlEncoded, TypeXFormUrlEncoded);

    default:
        return nullptr;
    }

#undef CASE_SWITCH
    return nullptr;
}

void _HttpMime::addNode(FileTypeSearchNode *root,
                                         const char *content, int size,
                                         int type) {
    int index = content[0] - 0x21;
    if (root->next[index] == nullptr) {
        root->next[index] = new FileTypeSearchNode();
    }

    FileTypeSearchNode *node = root->next[index];
    if (size == 1) {
        node->type = type;
        return;
    } else {
        char *p = ((char *)content) + 1;
        size--;
        addNode(node, p, size, type);
    }
}

int _HttpMime::searchNode(FileTypeSearchNode *root,
                                           const char *content, int size) {
    int index = content[0] - 0x21;
    if (root->next[index] == nullptr) {
        return -1;
    }

    size--;
    content++;
    if (size == 0) {
        return root->next[index]->type;
    } else {
        return searchNode(root->next[index], content, size);
    }
}

_HttpMime::_HttpMime() {
    static std::once_flag flag;
    std::call_once(flag, [&]() {
        mSuffixRootNode = new FileTypeSearchNode();
        mContentTypeNode = new FileTypeSearchNode();

    #define ADD_NODE(X, Y)                                                         \
        addNode(mSuffixRootNode, st(HttpMime)::X->toChars(),                \
                st(HttpMime)::X->size(), st(HttpMime)::Y)

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
        addNode(mContentTypeNode, st(HttpMime)::X->toChars(),               \
                st(HttpMime)::X->size(), st(HttpMime)::Y)

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

    mType = -1;   
}

} // namespace obotcha
