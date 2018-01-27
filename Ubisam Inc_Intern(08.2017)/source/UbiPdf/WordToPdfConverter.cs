using Word = Microsoft.Office.Interop.Word;

namespace UbiPdf
{
    /// <summary>
    /// Creator : 이도형 (esrenll@gmail.com)
    /// Create : 2017.08.07
    /// LastUpdate : 2017.08.17
    /// Description : 워드를 PDF로 변환시키는 클래스
    /// Usage : PdfConverter 클래스 참조
    /// </summary>
    class WordToPdfConverter : PdfConverter
    {
        /// <summary>
        /// 입력 워드 파일을 변환하여 PDF 파일로 저장
        /// </summary>
        /// <param name="inputFilePath">입력 파일 경로</param>
        /// <param name="outputFilePath">PDF 파일로 내보낼 경로</param>
        public override void convert(string inputFilePath, string outputFilePath)
        {
            Word.Application word = new Word.Application();
            Word.Document doc = word.Documents.Open(inputFilePath);
            doc.ExportAsFixedFormat(outputFilePath, Word.WdExportFormat.wdExportFormatPDF);
            doc.Close();
            word.Quit();
        }

        /// <summary>
        /// 변환할 수 있는 파일의 확장자들을 반환
        /// </summary>
        /// <returns></returns>
        public override string[] supportedExtension()
        {
            return new string[] { ".doc", ".docx" };
        }
    }
}
