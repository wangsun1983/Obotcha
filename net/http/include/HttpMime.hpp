#ifndef __OBOTCHA_HTTP_MIME_HPP__
#define __OBOTCHA_HTTP_MIME_HPP__

//according nginx/conf/mime.types
#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "HashMap.hpp"

namespace obotcha {

DECLARE_CLASS(HttpMime) {

public:
    enum class Type {
        TextHtml = 0,
        TextCss,
        TextXml,
        ImageGif,
        ImageJpeg,
        ApplicationJs,
        ApplicationAtomXml,
        ApplicationRss,
        TextMathml,
        TextPlain,
        TextVndSunJ2meAppDes,
        TextVndWapWml,
        TextXComponent,
        ImagePng,
        ImageSvgXml,
        ImageTiff,
        ImageVndWapWbmp,
        ImageWebp,
        ImageXIcon,
        ImageXJng,
        ImageXMsBmp,
        ApplicationFontWoff,
        ApplicationJavaArchive,
        ApplicationJson,
        ApplicationMaxBinhex40,
        ApplicationMsword,
        ApplicationPdf,
        ApplicationPostScript,
        ApplicationRtf,
        ApplicationVndAppleMpegurl,
        ApplicationVndGoogleEarthKmlXml,
        ApplicationVndGoogleEarthKmz,
        ApplicationVndMsExcel,
        ApplicationVndMsFontObject,
        ApplicationVndMsPpt,
        ApplicationVndOasisOpendocGraphics,
        ApplicationVndOasisOpendocPresentation,
        ApplicationVndOasisOpendocSpreadsheet,
        ApplicationVndOasisOpendocText,
        ApplicationVndOpenxmlPresentation,
        ApplicationVndOpenXmlSheet,
        ApplicationVndOepnXmlDoc,
        ApplicationVndWapWmls,
        Application7z,
        ApplicationXCocoa,
        ApplicationXJavaArch,
        ApplicationXJavaJnlpFile,
        ApplicationXMakeself,
        ApplicationXPerl,
        ApplicationXPilot,
        ApplicationXRarCompressed,
        ApplicationXReadhatPkgManager,
        ApplicationXSea,
        ApplicationXShockwaveFlash,
        ApplicationXStuffit,
        ApplicationXTcl,
        ApplicationXX509CaCert,
        ApplicationXXpinstall,
        ApplicationXhtmlXml,
        ApplicationXspfXml,
        ApplicationZip,
        ApplicationOctetStream,
        AudioMidi,
        AudioMpeg,
        AudioOgg,
        AudioXM4a,
        AudioXRealAudio,
        Video3Gpp,
        VideoMp2t,
        VideoMp4,
        VideoMpeg,
        VidoQuicktime,
        VideoWebm,
        VideoXflv,
        VideoXM4v,
        VideoXMng,
        VideoXMsAsf,
        VideoXMsWmv,
        VideoXMsVideo,
        MultiPartFormData,
        XFormUrlEncoded,
    };
    
    /**
    * type:
    * text/html
    * suffix:
    * html,htm,shtml
    **/ 
    static const String TextHtml;
    static const String SuffixHtml;
    static const String SuffixHtm;
    static const String SuffixShtml;

    /**
    * type:
    * text/css
    * suffix:
    * css
    **/ 
    static const String TextCss;
    static const String SuffixCss;

    /**
    * type:
    * text/xml
    * suffix:
    * xml
    **/ 
    static const String TextXml;
    static const String SuffixXml;

    /**
    * type:
    * image/gif
    * suffix:
    * gif
    **/ 
    static const String ImageGif;
    static const String SuffixGif;

    /**
    * type:
    * image/jpeg
    * suffix:
    * jpeg or jpg
    **/ 
    static const String ImageJpeg;
    static const String SuffixJpeg;
    static const String SuffixJpg;

    /**
    * type:
    * application/javascript
    * suffix:
    * js
    **/
    static const String ApplicationJs;
    static const String SuffixJs;

    /**
    * type:
    * application/atom+xml
    * suffix:
    * atom
    **/
    static const String ApplicationAtomXml;
    static const String SuffixAtom;

    /**
    * type:
    * application/rss+xml
    * suffix:
    * rss
    **/
    static const String ApplicationRss;
    static const String SuffixRss;

    /**
    * type:
    * text/mathml
    * suffix:
    * mml
    **/
    static const String TextMathml;
    static const String SuffixMml;

    /**
    * type:
    * text/plain
    * suffix:
    * txt
    **/
    static const String TextPlain;
    static const String SuffixTxt;

    /**
    * type:
    * text/vnd.sun.j2me.app-descriptor
    * suffix:
    * jad
    **/
    static const String TextVndSunJ2meAppDes;
    static const String SuffixJad;

    /**
    * type:
    * text/vnd.wap.wml
    * suffix:
    * wml
    **/
    static const String TextVndWapWml;
    static const String SuffixWml;

    /**
    * type:
    * text/x-component
    * suffix:
    * htc
    **/
    static const String TextXComponent;
    static const String SuffixHtc;

    /**
    * type:
    * image/png
    * suffix:
    * png
    **/
    static const String ImagePng;
    static const String SuffixPng;

    /**
    * type:
    * image/svg+xml
    * suffix:
    * svg or svgz
    **/
    static const String ImageSvgXml;
    static const String SuffixSvg;
    static const String SuffixSvgz;

    /**
    * type:
    * image/tiff
    * suffix:
    * tif or tiff
    **/
    static const String ImageTiff;
    static const String SuffixTif;
    static const String SuffixTiff;

    /**
    * type:
    * image/vnd.wap.wbmp
    * suffix:
    * wbmp
    **/
    static const String ImageVndWapWbmp;
    static const String SuffixWbmp;

    /**
    * type:
    * image/webp
    * suffix:
    * webp
    **/
    static const String ImageWebp;
    static const String SuffixWebp;

    /**
    * type:
    * image/x-icon
    * suffix:
    * ico
    **/
    static const String ImageXIcon;
    static const String SuffixIco;

    /**
    * type:
    * image/x-jng
    * suffix:
    * jng
    **/
    static const String ImageXJng;
    static const String SuffixJng;

    /**
    * type:
    * image/x-ms-bmp
    * suffix:
    * bmp
    **/
    static const String ImageXMsBmp;
    static const String SuffixBmp;

    /**
    * type:
    * application/font-woff
    * suffix:
    * woff
    **/
    static const String ApplicationFontWoff;
    static const String SuffixWoff;

    /**
    * type:
    * application/java-archive
    * suffix:
    * jar or war or ear
    **/
    static const String ApplicationJavaArchive;
    static const String SuffixJar;
    static const String SuffixWar;
    static const String SuffixEar;

    /**
    * type:
    * application/json
    * suffix:
    * json
    **/
    static const String ApplicationJson;
    static const String SuffixJson;

    /**
    * type:
    * application/mac-binhex40
    * suffix:
    * hqx
    **/
    static const String ApplicationMaxBinhex40;
    static const String SuffixHqx;

    /**
    * type:
    * application/msword
    * suffix:
    * doc
    **/
    static const String ApplicationMsword;
    static const String SuffixDoc;

    /**
    * type:
    * application/pdf
    * suffix:
    * pdf
    **/
    static const String ApplicationPdf;
    static const String SuffixPdf;

    /**
    * type:
    * application/postscript
    * suffix:
    * ps or eps or ai
    **/
    static const String ApplicationPostScript;
    static const String SuffixPs;
    static const String SuffixEps;
    static const String SuffixAi;

    /**
    * type:
    * application/rtf
    * suffix:
    * rtf
    **/
    static const String ApplicationRtf;
    static const String SuffixRtf;

    /**
    * type:
    * application/vnd.apple.mpegurl
    * suffix:
    * m3u8
    **/
    static const String ApplicationVndAppleMpegurl;
    static const String SuffixM3u8;

    /**
    * type:
    * application/vnd.google-earth.kml+xml
    * suffix:
    * kml
    **/
    static const String ApplicationVndGoogleEarthKmlXml;
    static const String SuffixKml;

    /**
    * type:
    * application/vnd.google-earth.kmz
    * suffix:
    * kmz
    **/
    static const String ApplicationVndGoogleEarthKmz;
    static const String SuffixKmz;

    /**
    * type:
    * application/vnd.ms-excel
    * suffix:
    * xls
    **/
    static const String ApplicationVndMsExcel;
    static const String SuffixXls;

    /**
    * type:
    * application/vnd.ms-fontobject
    * suffix:
    * eot
    **/
    static const String ApplicationVndMsFontObject;
    static const String SuffixEot;

    /**
    * type:
    * application/vnd.ms-powerpoint
    * suffix:
    * ppt
    **/
    static const String ApplicationVndMsPpt;
    static const String SuffixPpt;

    /**
    * type:
    * application/vnd.oasis.opendocument.graphics
    * suffix:
    * odg
    **/
    static const String ApplicationVndOasisOpendocGraphics;
    static const String SuffixOdj;

    /**
    * type:
    * application/vnd.oasis.opendocument.presentation
    * suffix:
    * odp
    **/
    static const String ApplicationVndOasisOpendocPresentation;
    static const String SuffixOdp;

    /**
    * type:
    * application/vnd.oasis.opendocument.spreadsheet
    * suffix:
    * ods
    **/
    static const String ApplicationVndOasisOpendocSpreadsheet;
    static const String SuffixOds;

    /**
    * type:
    * application/vnd.oasis.opendocument.text
    * suffix:
    * odt
    **/
    static const String ApplicationVndOasisOpendocText;
    static const String SuffixOdt;

    /**
    * type:
    * application/vnd.openxmlformats-officedocument.presentationml.presentation
    * suffix:
    * pptx
    **/
    static const String ApplicationVndOpenxmlPresentation;
    static const String SuffixPptx;

    /**
    * type:
    * application/vnd.openxmlformats-officedocument.spreadsheetml.sheet
    * suffix:
    * xlsx
    **/
    static const String ApplicationVndOpenXmlSheet;
    static const String SuffixXlsx;

    /**
    * type:
    * application/vnd.openxmlformats-officedocument.wordprocessingml.document
    * suffix:
    * docx
    **/
    static const String ApplicationVndOepnXmlDoc;
    static const String SuffixDocx;

    /**
    * type:
    * application/vnd.wap.wmlc 
    * suffix:
    * wmlc
    **/
    static const String ApplicationVndWapWmls;
    static const String SuffixWmlc;

    /**
    * type:
    * application/x-7z-compressed
    * suffix:
    * 7z
    **/
    static const String Application7z;
    static const String Suffix7z;

    /**
    * type:
    * application/x-cocoa
    * suffix:
    * cco
    **/
    static const String ApplicationXCocoa;
    static const String SuffixCco;

    /**
    * type:
    * application/x-java-archive-diff
    * suffix:
    * jardiff
    **/
    static const String ApplicationXJavaArch;
    static const String SuffixJardiff;

    /**
    * type:
    * application/x-java-jnlp-file
    * suffix:
    * jnlp
    **/
    static const String ApplicationXJavaJnlpFile;
    static const String SuffixJnlp;

    /**
    * type:
    * application/x-makeself
    * suffix:
    * run
    **/
    static const String ApplicationXMakeself;
    static const String SuffixRun;

    /**
    * type:
    * application/x-perl
    * suffix:
    * pl or pm
    **/
    static const String ApplicationXPerl;
    static const String SuffixPl;
    static const String SuffixPm;

    /**
    * type:
    * application/x-pilot
    * suffix:
    * prc or pdb
    **/
    static const String ApplicationXPilot;
    static const String SuffixPrc;
    static const String SuffixPdb;

    /**
    * type:
    * application/x-rar-compressed
    * suffix:
    * rar
    **/
    static const String ApplicationXRarCompressed;
    static const String SuffixRar;

    /**
    * type:
    * application/x-redhat-package-manager
    * suffix:
    * rpm
    **/
    static const String ApplicationXReadhatPkgManager;
    static const String SuffixRpm;

    /**
    * type:
    * application/x-sea
    * suffix:
    * sea
    **/
    static const String ApplicationXSea;
    static const String SuffixSea;

    /**
    * type:
    * application/x-shockwave-flash
    * suffix:
    * swf
    **/
    static const String ApplicationXShockwaveFlash;
    static const String SuffixSwf;

    /**
    * type:
    * application/x-stuffit
    * suffix:
    * sit
    **/
    static const String ApplicationXStuffit;
    static const String SuffixSit;

    /**
    * type:
    * application/x-tcl
    * suffix:
    * tcl or tk
    **/
    static const String ApplicationXTcl;
    static const String SuffixTcl;
    static const String SuffixTk;

    /**
    * type:
    * application/x-x509-ca-cert
    * suffix:
    * der or pem or crt
    **/
    static const String ApplicationXX509CaCert;
    static const String SuffixDer;
    static const String SuffixPem;
    static const String SuffixCrt;

    /**
    * type:
    * application/x-xpinstall
    * suffix:
    * xpi
    **/
    static const String ApplicationXXpinstall;
    static const String SuffixXpi;

    /**
    * type:
    * application/xhtml+xml
    * suffix:
    * xhtml
    **/
    static const String ApplicationXhtmlXml;
    static const String SuffixXhtml;

    /**
    * type:
    * application/xspf+xml 
    * suffix:
    * xspf
    **/
    static const String ApplicationXspfXml;
    static const String SuffixXspf;

    /**
    * type:
    * application/zip
    * suffix:
    * zip
    **/
    static const String ApplicationZip;
    static const String SuffixZip;

    /**
    * type:
    * application/octet-stream
    * suffix:
    * bin exe dll deb dmg iso img msi msp msm
    **/
    static const String ApplicationOctetStream;
    static const String SuffixBin;
    static const String SuffixExe;
    static const String SuffixDll;
    static const String SuffixDeb;
    static const String SuffixDmg;
    static const String SuffixIso;
    static const String SuffixImg;
    static const String SuffixMsi;
    static const String SuffixMsp;
    static const String SuffixMsm;

    /**
    * type:
    * audio/midi
    * suffix:
    * mid or midi or kar
    **/
    static const String AudioMidi;
    static const String SuffixMid;
    static const String SuffixMidi;
    static const String SuffixKar;

    /**
    * type:
    * audio/mpeg
    * suffix:
    * mp3
    **/
    static const String AudioMpeg;
    static const String SuffixMp3;

    /**
    * type:
    * audio/ogg
    * suffix:
    * ogg
    **/
    static const String AudioOgg;
    static const String SuffixOgg;

    /**
    * type:
    * audio/x-m4a
    * suffix:
    * m4a
    **/
    static const String AudioXM4a;
    static const String SuffixM4a;

    /**
    * type:
    * audio/x-realaudio   
    * suffix:
    * ra
    **/
    static const String AudioXRealAudio;
    static const String SuffixRa;

    /**
    * type:
    * video/3gpp
    * suffix:
    * 3gpp or 3gp
    **/
    static const String Video3Gpp;
    static const String Suffix3Gpp;
    static const String Sufix3Gp;

    /**
    * type:
    * video/mp2t
    * suffix:
    * ts
    **/
    static const String VideoMp2t;
    static const String SuffixTs;

    /**
    * type:
    * video/mp4
    * suffix:
    * mp4
    **/
    static const String VideoMp4;
    static const String SuffixMp4;

    /**
    * type:
    * video/mpeg
    * suffix:
    * mpeg or mpg
    **/
    static const String VideoMpeg;
    static const String SuffixMpeg;
    static const String SuffixMpg;

    /**
    * type:
    * video/quicktime
    * suffix:
    * mov
    **/
    static const String VidoQuicktime;
    static const String SuffixMov;

    /**
    * type:
    * video/webm 
    * suffix:
    * webm
    **/
    static const String VideoWebm;
    static const String SuffixWebm;

    /**
    * type:
    * video/x-flv
    * suffix:
    * flv
    **/
    static const String VideoXflv;
    static const String SuffixFlv;

    /**
    * type:
    * video/x-m4v
    * suffix:
    * m4v
    **/
    static const String VideoXM4v;
    static const String SuffixM4V;

    /**
    * type:
    * video/x-mng
    * suffix:
    * mng
    **/
    static const String VideoXMng;
    static const String SuffixMng;

    /**
    * type:
    * video/x-ms-asf
    * suffix:
    * asx or asf
    **/
    static const String VideoXMsAsf;
    static const String SuffixAsx;
    static const String SuffixAsf;

    /**
    * type:
    * video/x-ms-wmv
    * suffix:
    * wmv
    **/
    static const String VideoXMsWmv;
    static const String SuffixWmv;

    /**
    * type:
    * video/x-msvideo
    * suffix:
    * avi
    **/
    static const String VideoXMsVideo;
    static const String SuffixAvi;


    // multipart/form-data
    static const String MultiPartFormData;
    static const String FormData;
    static const String Boundary;

    // x-www-form-urlencoded
    static const String XFormUrlEncoded;

    // CharSet
    static const String CharSet;

    _HttpMime();
    
    sp<_HttpMime> setSuffix(String);
    sp<_HttpMime> setType(String);
    sp<_HttpMime> setTypeId(_HttpMime::Type);

    ArrayList<String> getSuffixs();
    _HttpMime::Type getTypeId() const;
    String getType() const;

private:
    String getType(_HttpMime::Type) const;

    static HashMap<String,Integer> nameToId;
    static HashMap<String,Integer> suffixToId;

    _HttpMime::Type mTypeId;
    String mType;
    ArrayList<String> mSuffixs;
};

}
#endif
