#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpContentType.hpp"

using namespace obotcha;

void check(String suffix,int expectedId) {
  HttpMime mime = createHttpMime();
  mime->setSuffix(suffix);
  if(mime->getTypeId() != expectedId) {
    printf("---[TestHttpMime suffix to id case1] [FAILED]---,id is %d,expectedId is %d,suffix is %s \n",mime->getTypeId(),expectedId,suffix->toChars());
  }
}

void testSuffixIdConvert() {
  check(st(HttpContentType)::SuffixHtml,st(HttpContentType)::TypeTextHtml);
  check(st(HttpContentType)::SuffixHtm,st(HttpContentType)::TypeTextHtml);
  check(st(HttpContentType)::SuffixShtml,st(HttpContentType)::TypeTextHtml);

  check(st(HttpContentType)::SuffixCss,st(HttpContentType)::TypeTextCss);

  check(st(HttpContentType)::SuffixXml,st(HttpContentType)::TypeTextXml);

  check(st(HttpContentType)::SuffixGif,st(HttpContentType)::TypeImageGif);

  check(st(HttpContentType)::SuffixJpeg,st(HttpContentType)::TypeImageJpeg);
  check(st(HttpContentType)::SuffixJpg,st(HttpContentType)::TypeImageJpeg);

  check(st(HttpContentType)::SuffixJs,st(HttpContentType)::TypeApplicationJs);

  check(st(HttpContentType)::SuffixAtom,st(HttpContentType)::TypeApplicationAtomXml);

  check(st(HttpContentType)::SuffixRss,st(HttpContentType)::TypeApplicationRss);

  check(st(HttpContentType)::SuffixMml,st(HttpContentType)::TypeTextMathml);

  check(st(HttpContentType)::SuffixTxt,st(HttpContentType)::TypeTextPlain);

  check(st(HttpContentType)::SuffixJad,st(HttpContentType)::TypeTextVndSunJ2meAppDes);

  check(st(HttpContentType)::SuffixWml,st(HttpContentType)::TypeTextVndWapWml);

  check(st(HttpContentType)::SuffixHtc,st(HttpContentType)::TypeTextXComponent);

  check(st(HttpContentType)::SuffixPng,st(HttpContentType)::TypeImagePng);

  check(st(HttpContentType)::SuffixSvg,st(HttpContentType)::TypeImageSvgXml);
  check(st(HttpContentType)::SuffixSvgz,st(HttpContentType)::TypeImageSvgXml);

  check(st(HttpContentType)::SuffixTif,st(HttpContentType)::TypeImageTiff);
  check(st(HttpContentType)::SuffixTiff,st(HttpContentType)::TypeImageTiff);

  check(st(HttpContentType)::SuffixWbmp,st(HttpContentType)::TypeImageVndWapWbmp);

  check(st(HttpContentType)::SuffixWebp,st(HttpContentType)::TypeImageWebp);

  check(st(HttpContentType)::SuffixIco,st(HttpContentType)::TypeImageXIcon);

  check(st(HttpContentType)::SuffixJng,st(HttpContentType)::TypeImageXJng);

  check(st(HttpContentType)::SuffixBmp,st(HttpContentType)::TypeImageXMsBmp);

  check(st(HttpContentType)::SuffixWoff,st(HttpContentType)::TypeApplicationFontWoff);

  check(st(HttpContentType)::SuffixJar,st(HttpContentType)::TypeApplicationJavaArchive);
  check(st(HttpContentType)::SuffixWar,st(HttpContentType)::TypeApplicationJavaArchive);
  check(st(HttpContentType)::SuffixEar,st(HttpContentType)::TypeApplicationJavaArchive);

  check(st(HttpContentType)::SuffixJson,st(HttpContentType)::TypeApplicationJson);

  check(st(HttpContentType)::SuffixHqx,st(HttpContentType)::TypeApplicationMaxBinhex40);

  check(st(HttpContentType)::SuffixDoc,st(HttpContentType)::TypeApplicationMsword);

  check(st(HttpContentType)::SuffixPdf,st(HttpContentType)::TypeApplicationPdf);

  check(st(HttpContentType)::SuffixPs,st(HttpContentType)::TypeApplicationPostScript);
  check(st(HttpContentType)::SuffixEps,st(HttpContentType)::TypeApplicationPostScript);
  check(st(HttpContentType)::SuffixAi,st(HttpContentType)::TypeApplicationPostScript);

  check(st(HttpContentType)::SuffixRtf,st(HttpContentType)::TypeApplicationRtf);

  check(st(HttpContentType)::SuffixM3u8,st(HttpContentType)::TypeApplicationVndAppleMpegurl);

  check(st(HttpContentType)::SuffixKml,st(HttpContentType)::TypeApplicationVndGoogleEarthKmlXml);

  check(st(HttpContentType)::SuffixKmz,st(HttpContentType)::TypeApplicationVndGoogleEarthKmz);

  check(st(HttpContentType)::SuffixXls,st(HttpContentType)::TypeApplicationVndMsExcel);

  check(st(HttpContentType)::SuffixEot,st(HttpContentType)::TypeApplicationVndMsFontObject);

  check(st(HttpContentType)::SuffixPpt,st(HttpContentType)::TypeApplicationVndMsPpt);

  check(st(HttpContentType)::SuffixOdj,st(HttpContentType)::TypeApplicationVndOasisOpendocGraphics);

  check(st(HttpContentType)::SuffixOdp,st(HttpContentType)::TypeApplicationVndOasisOpendocPresentation);

  check(st(HttpContentType)::SuffixOds,st(HttpContentType)::TypeApplicationVndOasisOpendocSpreadsheet);

  check(st(HttpContentType)::SuffixOdt,st(HttpContentType)::TypeApplicationVndOasisOpendocText);

  check(st(HttpContentType)::SuffixPptx,st(HttpContentType)::TypeApplicationVndOpenxmlPresentation);

  check(st(HttpContentType)::SuffixXlsx,st(HttpContentType)::TypeApplicationVndOpenXmlSheet);

  check(st(HttpContentType)::SuffixDocx,st(HttpContentType)::TypeApplicationVndOepnXmlDoc);

  check(st(HttpContentType)::SuffixWmlc,st(HttpContentType)::TypeApplicationVndWapWmls);

  check(st(HttpContentType)::Suffix7z,st(HttpContentType)::TypeApplication7z);

  check(st(HttpContentType)::SuffixCco,st(HttpContentType)::TypeApplicationXCocoa);

  check(st(HttpContentType)::SuffixJardiff,st(HttpContentType)::TypeApplicationXJavaArch);

  check(st(HttpContentType)::SuffixJnlp,st(HttpContentType)::TypeApplicationXJavaJnlpFile);

  check(st(HttpContentType)::SuffixRun,st(HttpContentType)::TypeApplicationXMakeself);

  check(st(HttpContentType)::SuffixPl,st(HttpContentType)::TypeApplicationXPerl);
  check(st(HttpContentType)::SuffixPm,st(HttpContentType)::TypeApplicationXPerl);

  check(st(HttpContentType)::SuffixPrc,st(HttpContentType)::TypeApplicationXPilot);
  check(st(HttpContentType)::SuffixPdb,st(HttpContentType)::TypeApplicationXPilot);

  check(st(HttpContentType)::SuffixRar,st(HttpContentType)::TypeApplicationXRarCompressed);

  check(st(HttpContentType)::SuffixRpm,st(HttpContentType)::TypeApplicationXReadhatPkgManager);

  check(st(HttpContentType)::SuffixSea,st(HttpContentType)::TypeApplicationXSea);

  check(st(HttpContentType)::SuffixSwf,st(HttpContentType)::TypeApplicationXShockwaveFlash);

  check(st(HttpContentType)::SuffixSit,st(HttpContentType)::TypeApplicationXStuffit);

  check(st(HttpContentType)::SuffixTcl,st(HttpContentType)::TypeApplicationXTcl);
  check(st(HttpContentType)::SuffixTk,st(HttpContentType)::TypeApplicationXTcl);

  check(st(HttpContentType)::SuffixDer,st(HttpContentType)::TypeApplicationXX509CaCert);
  check(st(HttpContentType)::SuffixPem,st(HttpContentType)::TypeApplicationXX509CaCert);
  check(st(HttpContentType)::SuffixCrt,st(HttpContentType)::TypeApplicationXX509CaCert);

  check(st(HttpContentType)::SuffixXpi,st(HttpContentType)::TypeApplicationXXpinstall);

  check(st(HttpContentType)::SuffixXhtml,st(HttpContentType)::TypeApplicationXhtmlXml);

  check(st(HttpContentType)::SuffixXspf,st(HttpContentType)::TypeApplicationXspfXml);

  check(st(HttpContentType)::SuffixZip,st(HttpContentType)::TypeApplicationZip);

  check(st(HttpContentType)::SuffixBin,st(HttpContentType)::TypeApplicationOctetStream);
  check(st(HttpContentType)::SuffixExe,st(HttpContentType)::TypeApplicationOctetStream);
  check(st(HttpContentType)::SuffixDll,st(HttpContentType)::TypeApplicationOctetStream);
  check(st(HttpContentType)::SuffixDeb,st(HttpContentType)::TypeApplicationOctetStream);
  check(st(HttpContentType)::SuffixDmg,st(HttpContentType)::TypeApplicationOctetStream);
  check(st(HttpContentType)::SuffixIso,st(HttpContentType)::TypeApplicationOctetStream);
  check(st(HttpContentType)::SuffixImg,st(HttpContentType)::TypeApplicationOctetStream);
  check(st(HttpContentType)::SuffixMsi,st(HttpContentType)::TypeApplicationOctetStream);
  check(st(HttpContentType)::SuffixMsp,st(HttpContentType)::TypeApplicationOctetStream);
  check(st(HttpContentType)::SuffixMsm,st(HttpContentType)::TypeApplicationOctetStream);
  check(st(HttpContentType)::SuffixImg,st(HttpContentType)::TypeApplicationOctetStream);

  check(st(HttpContentType)::SuffixMid,st(HttpContentType)::TypeAudioMidi);
  check(st(HttpContentType)::SuffixMidi,st(HttpContentType)::TypeAudioMidi);
  check(st(HttpContentType)::SuffixKar,st(HttpContentType)::TypeAudioMidi);

  check(st(HttpContentType)::SuffixMp3,st(HttpContentType)::TypeAudioMpeg);

  check(st(HttpContentType)::SuffixOgg,st(HttpContentType)::TypeAudioOgg);

  check(st(HttpContentType)::SuffixM4a,st(HttpContentType)::TypeAudioXM4a);

  check(st(HttpContentType)::SuffixRa,st(HttpContentType)::TypeAudioXRealAudio);

  check(st(HttpContentType)::Suffix3Gpp,st(HttpContentType)::TypeVideo3Gpp);
  check(st(HttpContentType)::Sufix3Gp,st(HttpContentType)::TypeVideo3Gpp);

  check(st(HttpContentType)::SuffixTs,st(HttpContentType)::TypeVideoMp2t);

  check(st(HttpContentType)::SuffixMp4,st(HttpContentType)::TypeVideoMp4);

  check(st(HttpContentType)::SuffixMpeg,st(HttpContentType)::TypeVideoMpeg);
  check(st(HttpContentType)::SuffixMpg,st(HttpContentType)::TypeVideoMpeg);

  check(st(HttpContentType)::SuffixMov,st(HttpContentType)::TypeVidoQuicktime);

  check(st(HttpContentType)::SuffixWebm,st(HttpContentType)::TypeVideoWebm);

  check(st(HttpContentType)::SuffixFlv,st(HttpContentType)::TypeVideoXflv);

  check(st(HttpContentType)::SuffixM4V,st(HttpContentType)::TypeVideoXM4v);

  check(st(HttpContentType)::SuffixMng,st(HttpContentType)::TypeVideoXMng);

  check(st(HttpContentType)::SuffixAsx,st(HttpContentType)::TypeVideoXMsAsf);
  check(st(HttpContentType)::SuffixAsf,st(HttpContentType)::TypeVideoXMsAsf);

  check(st(HttpContentType)::SuffixWmv,st(HttpContentType)::TypeVideoXMsWmv);

  check(st(HttpContentType)::SuffixAvi,st(HttpContentType)::TypeVideoXMsVideo);

  printf("---[TestHttpMime suffix to id case100] [OK]--- \n");
}
