//according nginx/conf/mime.types

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "HttpCookie.hpp"
#include "Mutex.hpp"
#include "File.hpp"
#include "HttpContentTypeTool.hpp"
#include "AutoLock.hpp"
#include "HttpContentType.hpp"

namespace obotcha {

Mutex _HttpContentTypeTool::mMutex = createMutex();
sp<_HttpContentTypeTool> _HttpContentTypeTool::mInstance = nullptr;

sp<_HttpContentTypeTool> _HttpContentTypeTool::getInstance() {
    if(mInstance != nullptr) {
        return mInstance;
    }

    AutoLock l(mMutex);
    if(mInstance != nullptr) {
        return mInstance;
    }

    _HttpContentTypeTool *p = new _HttpContentTypeTool();
    mInstance.set_pointer(p);
    return mInstance;
    
}


int _HttpContentTypeTool::typeToInt(String v) {
    String suffix = v->toLowerCase();
    return searchNode(mContentTypeNode,suffix->toChars(),suffix->size());
}

int _HttpContentTypeTool::suffixToInt(String v) {
    String suffix = v->toLowerCase();
    return searchNode(mSuffixRootNode,suffix->toChars(),suffix->size());
}

String _HttpContentTypeTool::suffixToType(String v) {
    int id = suffixToInt(v);
    return intToType(id);
}

String _HttpContentTypeTool::intToType(int id) {

#define CASE_SWITCH(X,Y) case st(HttpContentType)::Y:\
return st(HttpContentType)::X;

    switch(id) {
        CASE_SWITCH(TextHtml,TypeTextHtml);
        CASE_SWITCH(TextCss,TypeTextCss);
        CASE_SWITCH(TextXml,TypeTextXml);
        CASE_SWITCH(ImageGif,TypeImageGif);
        CASE_SWITCH(ImageJpeg,TypeImageJpeg);
        CASE_SWITCH(ApplicationJs,TypeApplicationJs);
        CASE_SWITCH(ApplicationAtomXml,TypeApplicationAtomXml);
        CASE_SWITCH(ApplicationRss,TypeApplicationRss);
        CASE_SWITCH(TextMathml,TypeMathml);
        CASE_SWITCH(TextPlain,TypeTextPlain);
        CASE_SWITCH(TextVndSunJ2meAppDes,TypeTextVndSunJ2meAppDes);
        CASE_SWITCH(TextVndWapWml,TypeVndWapWml);
        CASE_SWITCH(TextXComponent,TypeXComponent);
        CASE_SWITCH(ImagePng,TypeImagePng);
        CASE_SWITCH(ImageSvgXml,TypeImageSvgXml);
        CASE_SWITCH(ImageTiff,TypeImageTiff);
        CASE_SWITCH(ImageVndWapWbmp,TypeImageVndWapWbmp);
        CASE_SWITCH(ImageWebp,TypeImageWebp);
        CASE_SWITCH(ImageXIcon,TypeImageXIcon);
        CASE_SWITCH(ImageXMsBmp,TypeImageXMsBmp);
        CASE_SWITCH(ApplicationFontWoff,TypeApplicationFontWoff);
        CASE_SWITCH(ApplicationJavaArchive,TypeApplicationJavaArchive);
        CASE_SWITCH(ApplicationJson,TypeApplicationJson);
        CASE_SWITCH(ApplicationMaxBinhex40,TypeApplicationMaxBinhex40);
        CASE_SWITCH(ApplicationMsword,TypeApplicationMsword);
        CASE_SWITCH(ApplicationPdf,TypeApplicationPdf);
        CASE_SWITCH(ApplicationPostScript,TypeApplicationPostScript);
        CASE_SWITCH(ApplicationRtf,TypeApplicationRtf);
        CASE_SWITCH(ApplicationVndAppleMpegurl,TypeApplicationVndAppleMpegurl);
        CASE_SWITCH(ApplicationVndGoogleEarthKmlXml,TypeApplicationVndGoogleEarthKmlXml);
        CASE_SWITCH(ApplicationVndGoogleEarthKmz,TypeApplicationVndGoogleEarthKmz);
        CASE_SWITCH(ApplicationVndMsExcel,TypeApplicationVndMsExcel);
        CASE_SWITCH(ApplicationVndMsFontObject,TypeApplicationVndMsFontObject);
        CASE_SWITCH(ApplicationVndMsPpt,TypeApplicationVndMsPpt);
        CASE_SWITCH(ApplicationVndOasisOpendocGraphics,TypeApplicationVndOasisOpendocGraphics);
        CASE_SWITCH(ApplicationVndOasisOpendocPresentation,TypeApplicationVndOasisOpendocPresentation);
        CASE_SWITCH(ApplicationVndOasisOpendocSpreadsheet,TypeApplicationVndOasisOpendocSpreadsheet);
        CASE_SWITCH(ApplicationVndOasisOpendocText,TypeApplicationVndOasisOpendocText);
        CASE_SWITCH(ApplicationVndOpenxmlPresentation,TypeApplicationVndOpenxmlPresentation);
        CASE_SWITCH(ApplicationVndOpenXmlSheet,TypeApplicationVndOpenXmlSheet);
        CASE_SWITCH(ApplicationVndOepnXmlDoc,TypeApplicationVndOepnXmlDoc);
        CASE_SWITCH(ApplicationVndWapWmls,TypeApplicationVndWapWmls);
        CASE_SWITCH(Application7z,TypeApplication7z);
        CASE_SWITCH(ApplicationXCocoa,TypeApplicationXCocoa);
        CASE_SWITCH(ApplicationXJavaArch,TypeApplicationXJavaArch);
        CASE_SWITCH(ApplicationXJavaJnlpFile,TypeApplicationXJavaJnlpFile);
        CASE_SWITCH(ApplicationXMakeself,TypeApplicationXMakeself);
        CASE_SWITCH(ApplicationXPerl,TypeApplicationXPerl);
        CASE_SWITCH(ApplicationXPilot,TypeApplicationXPilot);
        CASE_SWITCH(ApplicationXRarCompressed,TypeApplicationXRarCompressed);
        CASE_SWITCH(ApplicationXReadhatPkgManager,TypeApplicationXReadhatPkgManager);
        CASE_SWITCH(ApplicationXSea,TypeApplicationXSea);
        CASE_SWITCH(ApplicationXShockwaveFlash,TypeApplicationXShockwaveFlash);
        CASE_SWITCH(ApplicationXStuffit,TypeApplicationXStuffit);
        CASE_SWITCH(ApplicationXTcl,TypeApplicationXTcl);
        CASE_SWITCH(ApplicationXX509CaCert,TypeApplicationXX509CaCert);
        CASE_SWITCH(ApplicationXXpinstall,TypeApplicationXXpinstall);
        CASE_SWITCH(ApplicationXhtmlXml,TypeApplicationXhtmXml);
        CASE_SWITCH(ApplicationXspfXml,TypeApplicationXspfXml);
        CASE_SWITCH(ApplicationZip,TypeApplicationZip);
        CASE_SWITCH(ApplicationOctetStream,TypeApplicationOctetStream);
        CASE_SWITCH(AudioMidi,TypeAudioMidi);
        CASE_SWITCH(AudioMpeg,TypeAudioMpeg);
        CASE_SWITCH(AudioOgg,TypeAudioOgg);
        CASE_SWITCH(AudioXM4a,TypeAudioXM4a);
        CASE_SWITCH(AudioXRealAudio,TypeAudioXRealAudio);
        CASE_SWITCH(Video3Gpp,TypeVideo3Gpp);
        CASE_SWITCH(VideoMp2t,TypeVideoMp2t);
        CASE_SWITCH(VideoMp4,TypeVideoMp4);
        CASE_SWITCH(VideoMpeg,TypeVideoMpeg);
        CASE_SWITCH(VidoQuicktime,TypeVidoQuicktime);
        CASE_SWITCH(VideoWebm,TypeVideoWebm);
        CASE_SWITCH(VideoXflv,TypeVideoXflv);
        CASE_SWITCH(VideoXM4v,TypeVideoXM4v);
        CASE_SWITCH(VideoXMng,TypeVideoXMng);
        CASE_SWITCH(VideoXMsAsf,TypeVideoXMsAsf);
        CASE_SWITCH(VideoXMsWmv,TypeVideoXMsWmv);
        CASE_SWITCH(VideoXMsVideo,TypeVideoXMsVideo);
        CASE_SWITCH(MultiPartFormData,TypeMultiPartFormData);
        CASE_SWITCH(XFormUrlEncoded,TypeXFormUrlEncoded);
        
        default:
        return nullptr;
    }

#undef CASE_SWITCH
    return nullptr;
}

void _HttpContentTypeTool::addNode(FileTypeSearchNode *root,const char *content,int size,int type) {
    int index = content[0] - 0x21;
    if(root->next[index] == nullptr) {
        root->next[index] = new FileTypeSearchNode();
    }

    FileTypeSearchNode *node = root->next[index];
    if(size == 1) {
        node->type = type;
        return;
    } else {
        content++;
        size--;
        addNode(node,content,size,type);
    }
}

int _HttpContentTypeTool::searchNode(FileTypeSearchNode *root,const char *content,int size) {
    int index = content[0] - 0x21;
    printf("content is %c \n",content[0]);
    if(root->next[index] == nullptr) {
        return -1;
    }
    
    size--;
    content++;
    if(size == 0) {
        return root->next[index]->type;
    } else {
        return searchNode(root->next[index],content,size);
    }
}

_HttpContentTypeTool::_HttpContentTypeTool() {

    mSuffixRootNode = new FileTypeSearchNode();
    mContentTypeNode = new FileTypeSearchNode();

#define ADD_NODE(X,Y) addNode(mSuffixRootNode,st(HttpContentType)::X->toChars(), st(HttpContentType)::X->size(),st(HttpContentType)::Y)

    ADD_NODE(SuffixHtml,TypeTextHtml);
    ADD_NODE(SuffixHtm,TypeTextHtml);
    ADD_NODE(SuffixHtml,TypeTextHtml);
    ADD_NODE(SuffixShtml,TypeTextHtml);
    ADD_NODE(SuffixCss,TypeTextCss);
    ADD_NODE(SuffixXml,TypeTextXml);
    ADD_NODE(SuffixGif,TypeImageGif);
    ADD_NODE(SuffixJpeg,TypeImageJpeg);
    ADD_NODE(SuffixJpg,TypeImageJpeg);
    ADD_NODE(SuffixJs,TypeApplicationJs);
    ADD_NODE(SuffixAtom,TypeApplicationAtomXml);
    ADD_NODE(SuffixRss,TypeApplicationRss);
    ADD_NODE(SuffixMml,TypeMathml);
    ADD_NODE(SuffixTxt,TypeTextPlain);
    ADD_NODE(SuffixJad,TypeTextVndSunJ2meAppDes); 
    ADD_NODE(SuffixWml,TypeVndWapWml);
    ADD_NODE(SuffixHtc,TypeXComponent);
    ADD_NODE(SuffixPng,TypeImagePng);
    ADD_NODE(SuffixSvg,TypeImageSvgXml);
    ADD_NODE(SuffixSvgz,TypeImageSvgXml);
    ADD_NODE(SuffixTif,TypeImageTiff);
    ADD_NODE(SuffixWbmp,TypeImageVndWapWbmp);
    ADD_NODE(SuffixWebp,TypeImageWebp);
    ADD_NODE(SuffixIco,TypeImageXIcon);
    ADD_NODE(SuffixJng,TypeImageXJng);
    ADD_NODE(SuffixBmp,TypeImageXMsBmp);
    ADD_NODE(SuffixWoff,TypeApplicationFontWoff);
    ADD_NODE(SuffixJar,TypeApplicationJavaArchive);
    ADD_NODE(SuffixWar,TypeApplicationJavaArchive);
    ADD_NODE(SuffixEar,TypeApplicationJavaArchive);
    ADD_NODE(SuffixJson,TypeApplicationJson);
    ADD_NODE(SuffixHqx,TypeApplicationMaxBinhex40);
    ADD_NODE(SuffixDoc,TypeApplicationMsword);
    ADD_NODE(SuffixPdf,TypeApplicationPdf);
    ADD_NODE(SuffixAi,TypeApplicationPostScript);
    ADD_NODE(SuffixEps,TypeApplicationPostScript);
    ADD_NODE(SuffixPs,TypeApplicationPostScript);
    ADD_NODE(SuffixRtf,TypeApplicationRtf);
    ADD_NODE(SuffixM3u8,TypeApplicationVndAppleMpegurl);
    ADD_NODE(SuffixKml,TypeApplicationVndGoogleEarthKmlXml);
    ADD_NODE(SuffixKmz,TypeApplicationVndGoogleEarthKmz);
    ADD_NODE(SuffixXls,TypeApplicationVndMsExcel);
    ADD_NODE(SuffixEot,TypeApplicationVndMsFontObject);
    ADD_NODE(SuffixPpt,TypeApplicationVndMsPpt);
    ADD_NODE(SuffixOdj,TypeApplicationVndOasisOpendocGraphics);
    ADD_NODE(SuffixOdp,TypeApplicationVndOasisOpendocPresentation);
    ADD_NODE(SuffixOds,TypeApplicationVndOasisOpendocSpreadsheet);
    ADD_NODE(SuffixOdt,TypeApplicationVndOasisOpendocText);
    ADD_NODE(SuffixPptx,TypeApplicationVndOpenxmlPresentation);
    ADD_NODE(SuffixXlsx,TypeApplicationVndOpenXmlSheet);
    ADD_NODE(SuffixDocx,TypeApplicationVndOepnXmlDoc);
    ADD_NODE(SuffixWmlc,TypeApplicationVndWapWmls);
    ADD_NODE(Suffix7z,TypeApplication7z);
    ADD_NODE(SuffixCco,TypeApplicationXCocoa);
    ADD_NODE(SuffixJardiff,TypeApplicationXJavaArch);
    ADD_NODE(SuffixJnlp,TypeApplicationXJavaJnlpFile);
    ADD_NODE(SuffixRun,TypeApplicationXMakeself);
    ADD_NODE(SuffixPl,TypeApplicationXPerl);
    ADD_NODE(SuffixPm,TypeApplicationXPerl);
    ADD_NODE(SuffixPrc,TypeApplicationXPilot);
    ADD_NODE(SuffixPdb,TypeApplicationXPilot);
    ADD_NODE(SuffixRar,TypeApplicationXRarCompressed);
    ADD_NODE(SuffixRpm,TypeApplicationXReadhatPkgManager);
    ADD_NODE(SuffixSea,TypeApplicationXSea);
    ADD_NODE(SuffixSwf,TypeApplicationXShockwaveFlash);
    ADD_NODE(SuffixSit,TypeApplicationXStuffit);
    ADD_NODE(SuffixTk,TypeApplicationXTcl);
    ADD_NODE(SuffixTcl,TypeApplicationXTcl);
    ADD_NODE(SuffixDer,TypeApplicationXX509CaCert);
    ADD_NODE(SuffixPem,TypeApplicationXX509CaCert);
    ADD_NODE(SuffixCrt,TypeApplicationXX509CaCert);
    ADD_NODE(SuffixXpi,TypeApplicationXXpinstall);
    ADD_NODE(SuffixXhtml,TypeApplicationXhtmXml);
    ADD_NODE(SuffixXspf,TypeApplicationXspfXml);
    ADD_NODE(SuffixZip,TypeApplicationZip);
    ADD_NODE(SuffixBin,TypeApplicationOctetStream);
    ADD_NODE(SuffixExe,TypeApplicationOctetStream);
    ADD_NODE(SuffixDll,TypeApplicationOctetStream);
    ADD_NODE(SuffixDeb,TypeApplicationOctetStream);
    ADD_NODE(SuffixDmg,TypeApplicationOctetStream);
    ADD_NODE(SuffixIso,TypeApplicationOctetStream);
    ADD_NODE(SuffixImg,TypeApplicationOctetStream);
    ADD_NODE(SuffixMsi,TypeApplicationOctetStream);
    ADD_NODE(SuffixMsp,TypeApplicationOctetStream);
    ADD_NODE(SuffixMsm,TypeApplicationOctetStream);
    ADD_NODE(SuffixMid,TypeAudioMidi);
    ADD_NODE(SuffixMidi,TypeAudioMidi);
    ADD_NODE(SuffixKar,TypeAudioMidi);
    ADD_NODE(SuffixMp3,TypeAudioMpeg);
    ADD_NODE(SuffixOgg,TypeAudioOgg);
    ADD_NODE(SuffixM4a,TypeAudioXM4a);
    ADD_NODE(SuffixRa,TypeAudioXRealAudio);
    ADD_NODE(Suffix3Gpp,TypeVideo3Gpp);
    ADD_NODE(Sufix3Gp,TypeVideo3Gpp);
    ADD_NODE(SuffixTs,TypeVideoMp2t);
    ADD_NODE(SuffixMp4,TypeVideoMp4);
    ADD_NODE(SuffixMpeg,TypeVideoMpeg);
    ADD_NODE(SuffixMpg,TypeVideoMpeg);
    ADD_NODE(SuffixMov,TypeVidoQuicktime);
    ADD_NODE(SuffixWebm,TypeVideoWebm);
    ADD_NODE(SuffixFlv,TypeVideoXflv);
    ADD_NODE(SuffixM4V,TypeVideoXM4v);
    ADD_NODE(SuffixMng,TypeVideoXMng);
    ADD_NODE(SuffixAsx,TypeVideoXMsAsf);
    ADD_NODE(SuffixAsf,TypeVideoXMsAsf);
    ADD_NODE(SuffixWmv,TypeVideoXMsWmv);
    ADD_NODE(SuffixAvi,TypeVideoXMsVideo);
#undef ADD_NODE

#define ADD_NODE(X,Y) addNode(mContentTypeNode,st(HttpContentType)::X->toChars(), st(HttpContentType)::X->size(),st(HttpContentType)::Y)

    ADD_NODE(TextHtml,TypeTextHtml);
    ADD_NODE(TextCss,TypeTextCss);
    ADD_NODE(TextXml,TypeTextXml);
    ADD_NODE(ImageGif,TypeImageGif);
    ADD_NODE(ImageJpeg,TypeImageJpeg);
    ADD_NODE(ApplicationJs,TypeApplicationJs);
    ADD_NODE(ApplicationAtomXml,TypeApplicationAtomXml);
    ADD_NODE(ApplicationRss,TypeApplicationRss);
    ADD_NODE(TextMathml,TypeMathml);
    ADD_NODE(TextPlain,TypeTextPlain);
    ADD_NODE(TextVndSunJ2meAppDes,TypeTextVndSunJ2meAppDes);
    ADD_NODE(TextVndWapWml,TypeVndWapWml);
    ADD_NODE(TextXComponent,TypeXComponent);
    ADD_NODE(ImagePng,TypeImagePng);
    ADD_NODE(ImageSvgXml,TypeImageSvgXml);
    ADD_NODE(ImageTiff,TypeImageTiff);
    ADD_NODE(ImageVndWapWbmp,TypeImageVndWapWbmp);
    ADD_NODE(ImageWebp,TypeImageWebp);
    ADD_NODE(ImageXIcon,TypeImageXIcon);
    ADD_NODE(ImageXMsBmp,TypeImageXMsBmp);
    ADD_NODE(ApplicationFontWoff,TypeApplicationFontWoff);
    ADD_NODE(ApplicationJavaArchive,TypeApplicationJavaArchive);
    ADD_NODE(ApplicationJson,TypeApplicationJson);
    ADD_NODE(ApplicationMaxBinhex40,TypeApplicationMaxBinhex40);
    ADD_NODE(ApplicationMsword,TypeApplicationMsword);
    ADD_NODE(ApplicationPdf,TypeApplicationPdf);
    ADD_NODE(ApplicationPostScript,TypeApplicationPostScript);
    ADD_NODE(ApplicationRtf,TypeApplicationRtf);
    ADD_NODE(ApplicationVndAppleMpegurl,TypeApplicationVndAppleMpegurl);
    ADD_NODE(ApplicationVndGoogleEarthKmlXml,TypeApplicationVndGoogleEarthKmlXml);
    ADD_NODE(ApplicationVndGoogleEarthKmz,TypeApplicationVndGoogleEarthKmz);
    ADD_NODE(ApplicationVndMsExcel,TypeApplicationVndMsExcel);
    ADD_NODE(ApplicationVndMsFontObject,TypeApplicationVndMsFontObject);
    ADD_NODE(ApplicationVndMsPpt,TypeApplicationVndMsPpt);
    ADD_NODE(ApplicationVndOasisOpendocGraphics,TypeApplicationVndOasisOpendocGraphics);
    ADD_NODE(ApplicationVndOasisOpendocPresentation,TypeApplicationVndOasisOpendocPresentation);
    ADD_NODE(ApplicationVndOasisOpendocSpreadsheet,TypeApplicationVndOasisOpendocSpreadsheet);
    ADD_NODE(ApplicationVndOasisOpendocText,TypeApplicationVndOasisOpendocText);
    ADD_NODE(ApplicationVndOpenxmlPresentation,TypeApplicationVndOpenxmlPresentation);
    ADD_NODE(ApplicationVndOpenXmlSheet,TypeApplicationVndOpenXmlSheet);
    ADD_NODE(ApplicationVndOepnXmlDoc,TypeApplicationVndOepnXmlDoc);
    ADD_NODE(ApplicationVndWapWmls,TypeApplicationVndWapWmls);
    ADD_NODE(Application7z,TypeApplication7z);
    ADD_NODE(ApplicationXCocoa,TypeApplicationXCocoa);
    ADD_NODE(ApplicationXJavaArch,TypeApplicationXJavaArch);
    ADD_NODE(ApplicationXJavaJnlpFile,TypeApplicationXJavaJnlpFile);
    ADD_NODE(ApplicationXMakeself,TypeApplicationXMakeself);
    ADD_NODE(ApplicationXPerl,TypeApplicationXPerl);
    ADD_NODE(ApplicationXPilot,TypeApplicationXPilot);
    ADD_NODE(ApplicationXRarCompressed,TypeApplicationXRarCompressed);
    ADD_NODE(ApplicationXReadhatPkgManager,TypeApplicationXReadhatPkgManager);
    ADD_NODE(ApplicationXSea,TypeApplicationXSea);
    ADD_NODE(ApplicationXShockwaveFlash,TypeApplicationXShockwaveFlash);
    ADD_NODE(ApplicationXStuffit,TypeApplicationXStuffit);
    ADD_NODE(ApplicationXTcl,TypeApplicationXTcl);
    ADD_NODE(ApplicationXX509CaCert,TypeApplicationXX509CaCert);
    ADD_NODE(ApplicationXXpinstall,TypeApplicationXXpinstall);
    ADD_NODE(ApplicationXhtmlXml,TypeApplicationXhtmXml);
    ADD_NODE(ApplicationXspfXml,TypeApplicationXspfXml);
    ADD_NODE(ApplicationZip,TypeApplicationZip);
    ADD_NODE(ApplicationOctetStream,TypeApplicationOctetStream);
    ADD_NODE(AudioMidi,TypeAudioMidi);
    ADD_NODE(AudioMpeg,TypeAudioMpeg);
    ADD_NODE(AudioOgg,TypeAudioOgg);
    ADD_NODE(AudioXM4a,TypeAudioXM4a);
    ADD_NODE(AudioXRealAudio,TypeAudioXRealAudio);
    ADD_NODE(Video3Gpp,TypeVideo3Gpp);
    ADD_NODE(VideoMp2t,TypeVideoMp2t);
    ADD_NODE(VideoMp4,TypeVideoMp4);
    ADD_NODE(VideoMpeg,TypeVideoMpeg);
    ADD_NODE(VidoQuicktime,TypeVidoQuicktime);
    ADD_NODE(VideoWebm,TypeVideoWebm);
    ADD_NODE(VideoXflv,TypeVideoXflv);
    ADD_NODE(VideoXM4v,TypeVideoXM4v);
    ADD_NODE(VideoXMng,TypeVideoXMng);
    ADD_NODE(VideoXMsAsf,TypeVideoXMsAsf);
    ADD_NODE(VideoXMsWmv,TypeVideoXMsWmv);
    ADD_NODE(VideoXMsVideo,TypeVideoXMsVideo);
    ADD_NODE(MultiPartFormData,TypeMultiPartFormData);
    ADD_NODE(XFormUrlEncoded,TypeXFormUrlEncoded);
#undef ADD_NODE

}

}
