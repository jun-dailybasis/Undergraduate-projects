using System;
using System.Collections.Generic;
using System.IO;

namespace UbiPdf
{
    /// <summary>
    /// Creator : 이도형 (esrenll@gmail.com)
    /// Create : 2017.08.17
    /// LastUpdate : 2017.08.17
    /// Description : 파일에 따라 PDF Converter를 선택, 변환시켜주는 클래스
    /// Usage :  1. 클래스 생성
    ///          2. 변환 (method convert)
    /// </summary>
    class ConvertManager
    {
        /// <summary>
        /// 사용 가능한 컨버터 리스트
        /// </summary>
        List<PdfConverter> converters = null;

        /// <summary>
        /// 생성자, 컨버터 리스트 초기화
        /// </summary>
        public ConvertManager()
        {
            converters = new List<PdfConverter>();
            converters.Add(new WordToPdfConverter());
        }

        /// <summary>
        /// 입력 파일의 확장자로 사용 가능한 컨버터 확인, 변환
        /// </summary>
        /// <param name="inputFilePath">입력 파일 경로</param>
        /// <param name="outputFilePath">출력 파일 경로</param>
        public void convert(string inputFilePath, string outputFilePath)
        {
            string extension = Path.GetExtension(inputFilePath);
            foreach (PdfConverter converter in converters)
            {
                foreach (string myext in converter.supportedExtension())
                {
                    if (myext.Equals(extension))
                    {
                        converter.convert(inputFilePath, outputFilePath);
                        return;
                    }
                }
            }
            throw new ExtensionNotSupportedException("Extension '" + extension + "' is not supported in ConvertManager.");
        }
    }

    /// <summary>
    /// 지원하지 않는 확장자에 대한 예외 클래스
    /// </summary>
    class ExtensionNotSupportedException : NotSupportedException
    {
        public ExtensionNotSupportedException(string message) : base(message) { }
    }

}
