using Ghostscript.NET;
using Ghostscript.NET.Rasterizer;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Reflection;
using System.Windows.Media.Imaging;

namespace UbiPdf
{
    /// <summary>
    /// Creator : 강예진, 이도형 (esrenll@gmail.com)
    /// Create : 2017.08.08
    /// LastUpdate : 2017.08.10
    /// Description : PDF를 이미지로 변환하는 클래스
    /// Usage :  1. 생성자 혹은 convert 메소드 사용
    ///          2. List<Image> Pages 로 가져오기
    /// License : MPL-2.0 (Ghostscript.NET), https://github.com/jhabjan/Ghostscript.NET/blob/master/COPYING
    /// </summary>
    public class PdfToImage
    {
        /// <summary>
        /// 변환된 각 페이지의 이미지를 담고 있는 리스트
        /// </summary>
        private List<Image> pages = new List<Image>();
        /// <summary>
        /// 변환된 각 페이지의 이미지를 담고 있는 리스트 접근
        /// </summary>
        public List<Image> Pages
        {
            get { return pages; }
        }
        /// <summary>
        /// 생성자
        /// </summary>
        public PdfToImage() { }
        /// <summary>
        /// 생성자, convert 메소드 호출
        /// </summary>
        /// <param name="filePath"></param>
        /// <param name="dpi"></param>
        /// <param name="progressModel"></param>
        public PdfToImage(string filePath, int dpi, UbisamIntern_Project.Model.ProgressModel progressModel = null)
        {
            convert(filePath, dpi, progressModel);
        }
        /// <summary>
        /// 생성자, convert 메소드 호출
        /// </summary>
        /// <param name="filePath"></param>
        /// <param name="dpi"></param>
        /// <param name="firstPage"></param>
        /// <param name="lastPage"></param>
        /// <param name="progressModel"></param>
        public PdfToImage(string filePath, int dpi, int firstPage, int lastPage, UbisamIntern_Project.Model.ProgressModel progressModel = null)
        {
            convert(filePath, dpi, firstPage, lastPage, progressModel);
        }
        /// <summary>
        /// PDF 파일을 이미지로 변환하여 리스트(Pages)에 저장
        /// progressModel 중 pageNum, progressedSize만 변경. fileSize와 관련된 정보는 사전에 넣어두어야한다.
        /// </summary>
        /// <param name="filePath">PDF 파일 경로</param>
        /// <param name="dpi">이미지의 dpi</param>
        /// <param name="progressModel">진행 경과를 전달하기 위한 모델</param>
        public void convert(string filePath, int dpi, UbisamIntern_Project.Model.ProgressModel progressModel = null)
        {
            convert(filePath, dpi, 0, 0, progressModel, false);
        }
        /// <summary>
        /// PDF 파일의 특정 페이지 범위를 이미지로 변환하여 리스트(Pages)에 저장
        /// progressModel 중 pageNum, progressedSize만 변경. fileSize와 관련된 정보는 사전에 넣어두어야한다.
        /// </summary>
        /// <param name="filePath">PDF 파일 경로</param>
        /// <param name="dpi">이미지의 dpi</param>
        /// <param name="firstPage">시작 페이지</param>
        /// <param name="lastPage">끝 페이지</param>
        /// <param name="progressModel">진행 경과를 전달하기 위한 모델</param>
        public void convert(string filePath, int dpi, int firstPage, int lastPage, UbisamIntern_Project.Model.ProgressModel progressModel = null)
        {
            convert(filePath, dpi, firstPage, lastPage, progressModel, true);
        }
        /// <summary>
        /// PDF 파일을 이미지로 변환하여 리스트(Pages)에 저장하는 범용 메소드
        /// progressModel 중 pageNum, progressedSize만 변경. fileSize와 관련된 정보는 사전에 넣어두어야한다.
        /// </summary>
        /// <param name="filePath">PDF 파일 경로</param>
        /// <param name="dpi">이미지의 dpi</param>
        /// <param name="firstPage">시작 페이지</param>
        /// <param name="lastPage">끝 페이지</param>
        /// <param name="progressModel">진행 경과를 전달하기 위한 모델</param>
        /// <param name="isRangedPage">페이지 범위 사용 여부</param>
        private void convert(string filePath, int dpi, int firstPage, int lastPage, UbisamIntern_Project.Model.ProgressModel progressModel, bool isRangedPage)
        {
            if (progressModel != null) progressModel.CurrentPageNum = 0;
            string path = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);

            GhostscriptRasterizer rasterizer = null;
            GhostscriptVersionInfo vesion = new GhostscriptVersionInfo(new Version(0, 0, 0), path + @"\gsdll32.dll", string.Empty, GhostscriptLicense.GPL);
            using (rasterizer = new GhostscriptRasterizer())
            {
                rasterizer.Open(filePath, vesion, false);
                if (progressModel != null) progressModel.TotalPageNum = rasterizer.PageCount;
                for (int i = (isRangedPage ? firstPage : 1); i <= (isRangedPage ? Math.Min(lastPage, rasterizer.PageCount) : rasterizer.PageCount); i++)
                {
                    if (progressModel != null)
                    {
                        progressModel.CurrentPageNum = i;
                        progressModel.ProgressedSize += progressModel.CurrentFileSize / rasterizer.PageCount;
                        if (i >= rasterizer.PageCount)
                            progressModel.ProgressedSize += progressModel.CurrentFileSize % rasterizer.PageCount;
                    }
                    Image img = rasterizer.GetPage(dpi, dpi, i);
                    pages.Add(img);
                }
                rasterizer.Close();
            }
        }

        /// <summary>
        /// 저장된 리스트 초기화
        /// </summary>
        public void clear()
        {
            pages.Clear();
        }

        /// <summary>
        /// index의 이미지를 비트맵 이미지로 반환
        /// </summary>
        /// <param name="index"></param>
        /// <returns></returns>
        public BitmapImage getBitmapImage(int index)
        {
            return imageToBitmapImage(pages[index]);
        }

        /// <summary>
        /// Image를 BitmapImage로 변환하는 정적 메소드
        /// </summary>
        /// <param name="image">변환할 Image</param>
        /// <returns>변환된 BitmapImage</returns>
        public static BitmapImage imageToBitmapImage(Image image)
        {
            MemoryStream ms = new MemoryStream();
            image.Save(ms, ImageFormat.Bmp);
            ms.Seek(0, SeekOrigin.Begin);

            BitmapImage bitmapImage = new BitmapImage();
            bitmapImage.BeginInit();
            bitmapImage.StreamSource = ms;
            bitmapImage.EndInit();

            return bitmapImage;
        }

    }
}
