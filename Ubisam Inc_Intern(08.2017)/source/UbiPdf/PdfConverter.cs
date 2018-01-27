using System.IO;

namespace UbiPdf
{
    /// <summary>
    /// Creator : 이도형 (esrenll@gmail.com)
    /// Create : 2017.08.07
    /// LastUpdate : 2017.08.30 (메소드 이름을 보다 적절하게 수정)
    /// Description : 어떤 파일을 PDF로 변환시키는 추상 클래스
    /// Usage :  1. 클래스 생성
    ///          2. 파일 변환 (method convert)
    /// </summary>
    abstract class PdfConverter
    {
        /// <summary>
        /// 변환할 수 있는 파일의 확장자들을 반환. 하나 이상의 멤버를 가져야한다.
        /// </summary>
        /// <returns></returns>
        abstract public string[] supportedExtension();
        /// <summary>
        /// 입력 파일을 변환하여 PDF 파일로 저장
        /// </summary>
        /// <param name="inputFilePath">입력 파일 경로</param>
        /// <param name="outputFilePath">PDF 파일로 내보낼 경로</param>
        abstract public void convert(string inputFilePath, string outputFilePath);
        /// <summary>
        /// 입력 파일이 있는 폴더에 확장자만 PDF로 변경하여 저장
        /// </summary>
        /// <param name="inputFilePath">입력 파일 경로</param>
        public void writeSourceDirectory(string inputFilePath)
        {
            writeDestinationDirectory(inputFilePath, Path.GetFullPath(inputFilePath));
        }
        /// <summary>
        /// 입력 파일의 확장자만 변경하여 목적지 폴더에 저장
        /// </summary>
        /// <param name="inputFilePath">입력 파일 경로</param>
        /// <param name="dstDir">저장할 폴더</param>
        public void writeDestinationDirectory(string inputFilePath, string dstDir)
        {
            string outputFilePath = dstDir
                + Path.GetFileNameWithoutExtension(inputFilePath)
                + supportedExtension()[0];
            convert(inputFilePath, outputFilePath);
        }
    }
}
