using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Printing;

namespace UbiPdf
{
    /// <summary>
    /// Creator : 강예진, 이도형 (esrenll@gmail.com)
    /// Create : 2017.08.09
    /// LastUpdate : 2017.08.21 (ProgressModel 반영)
    /// Description : PDF를 프린트하는 클래스
    /// Usage :  1. 객체 생성
    ///          2. createPrintDocument 메소드가 PrintDocument 반환
    /// Option : 1. PrintDocument 생성시 옵션 지정 가능 - PrintOption 의 OR 연산으로 삽입
    /// License : MPL-2.0 (Ghostscript.NET), https://github.com/jhabjan/Ghostscript.NET/blob/master/COPYING
    /// </summary>
    class PdfPrint
    {
        /// <summary>
        /// PrintDocument 문서를 만들 때(메소드 createPrintDocument) 사용되는 옵션.
        /// Binary OR 연산 '|'을 사용하여 옵션 중첩.
        /// </summary>
        public enum Option
        {
            DEFAULT = 0x0,
            PAGE_BOUND = 0x1, WIDTH_BOUND = 0x2, HEIGHT_BOUND = 0x4, NOTCHANGE = 0x8,
            ROTATE90 = 0x10, ROTATE180 = 0x20, ROTATE270 = 0x40,
            PAGE1SLIDE1 = 0x100, PAGE1SLIDE2 = 0x200, PAGE1SLIDE4 = 0x400,
            SHOW_PAGENUM = 0x1000, SHOW_FILENAME = 0x2000, SHOW_PRINTDATE = 0x4000,
            DUPLEX_H = 0x10000, DUPLEX_V = 0x20000,
            INVALID = 0x7FFFFFFF
        }

        /// <summary>
        /// pdf를 이미지로 변환하고 변환된 이미지를 가지고 있는 객체
        /// </summary>
        private PdfToImage pdfToImage = new PdfToImage();
        /// <summary>
        /// 이미지로 변환한 각 페이지 별 파일 경로
        /// </summary>
        private List<string> filePathList = new List<string>();
        /// <summary>
        /// 이미지로 변환한 각 페이지의 파일 순서, 0부터 시작
        /// </summary>
        private List<int> fileNumList = new List<int>();
        /// <summary>
        /// 이미지로 변환한 각 페이지 별 페이지 번호
        /// </summary>
        private List<int> filePageNumList = new List<int>();
        /// <summary>
        /// 이미지로 변환한 각 페이지 별 파일의 총 페이지 갯수
        /// </summary>
        private List<int> fileTotalPageList = new List<int>();
        /// <summary>
        /// 이미지로 변환한 각 페이지 별 파일의 사이즈
        /// </summary>
        private List<long> fileSizeList = new List<long>();
        /// <summary>
        /// 마지막에 지정된 옵션
        /// </summary>
        private Option _option = Option.DEFAULT;

        /// <summary>
        /// 이미지로 변환한 페이지의 갯수
        /// </summary>
        public int Count
        {
            get { return pdfToImage.Pages.Count; }
        }

        /// <summary>
        /// 이미지로 변환한 페이지 중 특정 index의 비트맵 이미지를 반환
        /// </summary>
        /// <param name="index">BitmapImage를 가져올 페이지의 index</param>
        /// <returns>해당 index의 BitmapImage</returns>
        public System.Windows.Media.Imaging.BitmapImage getBitmapImage(int index)
        {
            return pdfToImage.getBitmapImage(index);
        }

        /// <summary>
        /// pdf 파일을 이미지로 변환
        /// progressModel 중 pageNum, progressedSize만 변경. fileSize와 관련된 정보는 사전에 넣어두어야한다.
        /// </summary>
        /// <param name="filePath">pdf 파일 경로</param>
        /// <param name="dpi">pdf 파일을 이미지로 변환할 때 dpi</param>
        /// <param name="progressModel">진행 경과를 전달하기 위한 모델</param>
        public void insertDocument(string filePath, int dpi, UbisamIntern_Project.Model.ProgressModel progressModel = null)
        {
            insertDocument(filePath, dpi, 0, 0, progressModel, false);
        }

        /// <summary>
        /// pdf 파일의 특정 페이지 범위를 이미지로 변환
        /// progressModel 중 pageNum, progressedSize만 변경. fileSize와 관련된 정보는 사전에 넣어두어야한다.
        /// </summary>
        /// <param name="filePath">pdf 파일 경로</param>
        /// <param name="dpi">pdf 파일을 이미지로 변환할 때 dpi</param>
        /// <param name="firstPage">시작 페이지 번호</param>
        /// <param name="lastPage">마지막 페이지 번호</param>
        /// <param name="progressModel">진행 경과를 전달하기 위한 모델</param>
        public void insertDocument(string filePath, int dpi, int firstPage, int lastPage, UbisamIntern_Project.Model.ProgressModel progressModel = null)
        {
            insertDocument(filePath, dpi, firstPage, lastPage, progressModel, true);
        }
        /// <summary>
        /// pdf 파일의 이미지로 변환하는 범용메소드
        /// progressModel 중 pageNum, progressedSize만 변경. fileSize와 관련된 정보는 사전에 넣어두어야한다.
        /// </summary>
        /// <param name="filePath"></param>
        /// <param name="dpi"></param>
        /// <param name="firstPage"></param>
        /// <param name="lastPage"></param>
        /// <param name="progressModel"></param>
        /// <param name="progressModel">진행 경과를 전달하기 위한 모델</param>
        /// <param name="isRanged"></param>
        private void insertDocument(string filePath, int dpi, int firstPage, int lastPage, UbisamIntern_Project.Model.ProgressModel progressModel, bool isRanged)
        {
            int imageCount = pdfToImage.Pages.Count;

            if (isRanged)
                pdfToImage.convert(filePath, dpi, firstPage, lastPage, progressModel);
            else
                pdfToImage.convert(filePath, dpi, progressModel);

            int fileNum = imageCount == 0 ? 0 : fileNumList[imageCount - 1] + 1;
            imageCount = pdfToImage.Pages.Count - imageCount;
            for (int i = 0; i < imageCount; ++i)
            {
                filePathList.Add(filePath);
                fileNumList.Add(fileNum);
                filePageNumList.Add(i + 1);
                fileTotalPageList.Add(imageCount);
                fileSizeList.Add(new System.IO.FileInfo(filePath).Length);
            }
        }

        /// <summary>
        /// 변환된 이미지들을 모두 초기화
        /// </summary>
        public void clearDocument()
        {
            pdfToImage.clear();
            filePathList.Clear();
        }

        /// <summary>
        /// 프린트(이미지)의 상단에 헤더를 추가
        /// </summary>
        /// <param name="image">헤더가 기록될 이미지</param>
        /// <param name="strAlignment">헤더 문자열의 정렬 기준</param>
        /// <param name="str">헤더에 기록할 문자열</param>
        public static void addPrintHeader(
            Image image, StringAlignment strAlignment, string str)
        {
            Graphics g = Graphics.FromImage(image);
            g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias;
            StringFormat stringFormat = new StringFormat();
            stringFormat.Alignment = strAlignment;
            stringFormat.LineAlignment = StringAlignment.Center;
            g.DrawString(str,
                new Font("Arial", 9),
                Brushes.Black,
                new RectangleF(30, 0, image.Width - 60, 80),
                stringFormat);
        }

        /// <summary>
        /// 마지막에 지정된 옵션에 따라 헤더 문자열을 생성, 반환
        /// </summary>
        /// <param name="imageIndex">헤더가 추가될 이미지 인덱스</param>
        /// <returns>생성된 헤더 문자열</returns>
        private string makePrintHeader(int imageIndex)
        {
            string header = "";
            if ((_option & Option.SHOW_PRINTDATE) == Option.SHOW_PRINTDATE)
                header += DateTime.Now.ToString("yyyy-M-d h:m:s tt") + "; \t";
            if ((_option & Option.SHOW_FILENAME) == Option.SHOW_FILENAME)
                header += filePathList[imageIndex] + "; \t";
            if ((_option & Option.SHOW_PAGENUM) == Option.SHOW_PAGENUM)
                header += filePageNumList[imageIndex] + "/" + fileTotalPageList[imageIndex];
            return header;
        }

        /// <summary>
        /// 옵션에 따라 image를 (reWidth, reHeight) 크기로 변환할 때의 adjustWidth
        /// 확장될 가로길이 = image.Width * adjustWidth
        /// </summary>
        /// <param name="image">변환될 이미지</param>
        /// <param name="reWidth">변환할 가로길이</param>
        /// <param name="reHeight">변환할 세로길이</param>
        /// <returns>image.Width에 곱할 조정값</returns>
        private float getAdjustWidth(Image image, int reWidth, int reHeight)
        {
            if ((_option & Option.NOTCHANGE) == Option.NOTCHANGE)
                return 1;
            else if ((_option & Option.WIDTH_BOUND) == Option.WIDTH_BOUND)
                return (float)reWidth / image.Width;
            else if ((_option & Option.HEIGHT_BOUND) == Option.HEIGHT_BOUND)
                return (float)reHeight / image.Height;
            else
                return (float)reWidth / image.Width;
        }
        /// <summary>
        /// 옵션에 따라 image를 (reWidth, reHeight) 크기로 변환할 때의 adjustHeight
        /// 확장될 세로길이 = image.Height * adjustHeight
        /// </summary>
        /// <param name="image">변환될 이미지</param>
        /// <param name="reWidth">변환할 가로길이</param>
        /// <param name="reHeight">변환할 세로길이</param>
        /// <returns>image.Height에 곱할 조정값</returns>
        private float getAdjustHeight(Image image, int reWidth, int reHeight)
        {
            if ((_option & Option.NOTCHANGE) == Option.NOTCHANGE)
                return 1;
            else if ((_option & Option.WIDTH_BOUND) == Option.WIDTH_BOUND)
                return (float)reWidth / image.Width;
            else if ((_option & Option.HEIGHT_BOUND) == Option.HEIGHT_BOUND)
                return (float)reHeight / image.Height;
            else
                return (float)reHeight / image.Height;
        }
        /// <summary>
        /// 한 페이지에 한 슬라이드를 인쇄할 때의 이미지를 생성, 반환
        /// </summary>
        /// <param name="imageIndex">페이지에 그릴 슬라이드의 인덱스</param>
        /// <param name="width">페이지의 가로 픽셀</param>
        /// <param name="height">페이지의 세로 픽셀</param>
        /// <returns>인쇄할 이미지</returns>
        private Image printPage1Slide1(ref int imageIndex, int width, int height)
        {
            bool rotate0 = ((_option & (Option.ROTATE90 | Option.ROTATE270)) == Option.DEFAULT);
            int beginWidth = 0, beginHeight = 0;
            if (rotate0)
            {
                beginWidth = width;
                beginHeight = height;
            }
            else
            {
                beginWidth = height;
                beginHeight = width;
            }
            Bitmap ret = new Bitmap(beginWidth, beginHeight);

            if (imageIndex < pdfToImage.Pages.Count)
            {
                float adjW = getAdjustWidth(pdfToImage.Pages[imageIndex], beginWidth, beginHeight);
                float adjH = getAdjustHeight(pdfToImage.Pages[imageIndex], beginWidth, beginHeight);

                Graphics g = Graphics.FromImage(ret);
                g.DrawImage(pdfToImage.Pages[imageIndex],
                    new RectangleF(0, 0, pdfToImage.Pages[imageIndex].Width * adjW, pdfToImage.Pages[imageIndex].Height * adjH));

                string header = makePrintHeader(imageIndex);
                addPrintHeader(ret, StringAlignment.Far, header);
            }
            ++imageIndex;
            rotateImage(ret);

            return ret;
        }

        /// <summary>
        /// 한 페이지에 두 슬라이드를 인쇄할 때의 이미지를 생성, 반환
        /// </summary>
        /// <param name="imageIndex">페이지에 그릴 슬라이드의 시작 인덱스</param>
        /// <param name="width">페이지의 가로 픽셀</param>
        /// <param name="height">페이지의 세로 픽셀</param>
        /// <returns>인쇄할 이미지</returns>
        private Image printPage1Slide2(ref int imageIndex, int width, int height)
        {
            Bitmap ret = new Bitmap(width, height);

            Graphics g = Graphics.FromImage(ret);
            g.DrawImage(printPage1Slide1(ref imageIndex, width, height / 2),
                new Rectangle(0, 0, width, height / 2));
            if (imageIndex < filePathList.Count && filePathList[imageIndex - 1] == filePathList[imageIndex])
                g.DrawImage(printPage1Slide1(ref imageIndex, width, height / 2),
                    new Rectangle(0, height / 2, width, height / 2));

            return ret;
        }

        /// <summary>
        /// 한 페이지에 네 개의 슬라이드를 인쇄할 때 이미지를 생성, 반환
        /// </summary>
        /// <param name="imageIndex">페이지에 그릴 슬라이드의 시작 인덱스</param>
        /// <param name="width">페이지의 가로 픽셀</param>
        /// <param name="height">페이지의 세로 픽셀</param>
        /// <returns>인쇄할 이미지</returns>
        private Image printPage1Slide4(ref int imageIndex, int width, int height)
        {
            Bitmap ret = new Bitmap(width, height);

            Graphics g = Graphics.FromImage(ret);
            int beginIndex = imageIndex;
            for (int r = 0; r < 2; ++r) for (int c = 0; c < 2; ++c)
                {
                    if (imageIndex >= filePathList.Count || filePathList[beginIndex] != filePathList[imageIndex])
                        break;

                    g.DrawImage(printPage1Slide1(ref imageIndex, width / 2, height / 2),
                        new Rectangle(width * c / 2, height * r / 2, width / 2, height / 2));
                }

            return ret;
        }

        /// <summary>
        /// 현재 옵션에 따라 이미지를 회전
        /// </summary>
        /// <param name="image">회전할 이미지</param>
        private void rotateImage(Image image)
        {
            RotateFlipType rotateFlipType = RotateFlipType.RotateNoneFlipNone;

            if ((_option & Option.ROTATE90) == Option.ROTATE90)
                rotateFlipType = RotateFlipType.Rotate90FlipNone;
            else if ((_option & Option.ROTATE180) == Option.ROTATE180)
                rotateFlipType = RotateFlipType.Rotate180FlipNone;
            else if ((_option & Option.ROTATE270) == Option.ROTATE270)
                rotateFlipType = RotateFlipType.Rotate270FlipNone;
            else
                return;

            image.RotateFlip(rotateFlipType);
        }

        /// <summary>
        /// 미리보기 이미지를 생성, 반환
        /// </summary>
        /// <param name="pageIndex">미리보기를 생성할 페이지의 인덱스</param>
        /// <param name="width">이미지의 가로 픽셀</param>
        /// <param name="height">이미지의 세로 픽셀</param>
        /// <param name="option"></param>
        /// <returns>미리보기 이미지</returns>
        public Image createPreviewImage(int pageIndex, int width, int height, Option option = Option.DEFAULT)
        {
            if ((option & Option.INVALID) == Option.INVALID) throw new InvalidPrintOptionException(
                 "Print Option is Invalid.");

            _option = option;
            int i = 1;
            if ((option & Option.PAGE1SLIDE2) == Option.PAGE1SLIDE2)
                i = pageIndex * 2;
            else if ((option & Option.PAGE1SLIDE2) == Option.PAGE1SLIDE2)
                i = pageIndex * 4;
            else
                i = pageIndex;

            return createPage(ref i, width, height);
        }

        /// <summary>
        /// 현재 옵션에 따라 페이지를 이미지로 생성, 반환
        /// </summary>
        /// <param name="imageIndex">페이지에 넣을 이미지 인덱스</param>
        /// <param name="width">페이지의 가로 픽셀</param>
        /// <param name="height">페이지의 세로 픽셀</param>
        /// <returns>생성된 페이지 이미지</returns>
        private Image createPage(ref int imageIndex, int width, int height)
        {
            Image page = null;

            if ((_option & Option.PAGE1SLIDE2) == Option.PAGE1SLIDE2)
                page = printPage1Slide2(ref imageIndex, width, height);
            else if ((_option & Option.PAGE1SLIDE4) == Option.PAGE1SLIDE4)
                page = printPage1Slide4(ref imageIndex, width, height);
            else
                page = printPage1Slide1(ref imageIndex, width, height);

            return page;
        }

        /// <summary>
        /// 인쇄를 위한 PrintDocument를 생성, 반환
        /// </summary>
        /// <param name="option">생성 옵션</param>
        /// <param name="progressModel">진행 경과를 전달하기 위한 모델</param>
        /// <returns></returns>
        public PrintDocument createPrintDocument(Option option = Option.DEFAULT, UbisamIntern_Project.Model.ProgressModel progressModel = null)
        {
            if ((option & Option.INVALID) == Option.INVALID) throw new InvalidPrintOptionException(
                 "Print Option is Invalid.");

            PrintDocument printDocument = new PrintDocument();
            _option = option;

            if ((option | Option.DUPLEX_H) == Option.DUPLEX_H)
                printDocument.PrinterSettings.Duplex = Duplex.Horizontal;
            else if ((option | Option.DUPLEX_V) == Option.DUPLEX_V)
                printDocument.PrinterSettings.Duplex = Duplex.Vertical;

            initializeProgressModel(progressModel);

            int i = 0;
            printDocument.PrintPage += delegate (object o, PrintPageEventArgs e)
            {
                updateProgressModel(i, progressModel);
                Image page = createPage(ref i, e.PageBounds.Width, e.PageBounds.Height);
                e.Graphics.DrawImage(page, new Rectangle(0, 0, e.PageBounds.Width, e.PageBounds.Height));

                e.HasMorePages = (i < pdfToImage.Pages.Count);
            };

            return printDocument;
        }
        private void initializeProgressModel(UbisamIntern_Project.Model.ProgressModel progressModel)
        {
            if (progressModel == null) return;

            int totalFileNum = fileNumList[fileNumList.Count - 1] + 1;
            long totalFileSize = 0;
            for (int i = 0; i <= fileNumList[fileNumList.Count - 1]; ++i)
                totalFileSize += fileSizeList[fileNumList.BinarySearch(i)];

            progressModel.TotalFileSize = totalFileSize;
            progressModel.TotalFileNum = totalFileNum;
        }
        private void updateProgressModel(int index, UbisamIntern_Project.Model.ProgressModel progressModel)
        {
            if (progressModel == null) return;

            progressModel.CurrentFileNum = fileNumList[index] + 1;
            progressModel.CurrentPageNum = filePageNumList[index];
            progressModel.FileName = filePathList[index];
            progressModel.CurrentFileSize = fileSizeList[index];
            progressModel.TotalPageNum = fileTotalPageList[index];
            progressModel.ProgressedSize += fileSizeList[index] / fileTotalPageList[index];
            if (index + 1 >= fileNumList.Count || filePathList[index] != filePathList[index + 1])
                progressModel.ProgressedSize += fileSizeList[index] % fileTotalPageList[index];
        }
    }

    /// <summary>
    /// 유효하지 않은 프린트 옵션을 사용한 경우 발생하는 예외 클래스
    /// </summary>
    class InvalidPrintOptionException : InvalidOperationException
    {
        public InvalidPrintOptionException(string msg) : base(msg) { }
    }
}