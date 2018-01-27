using iTextSharp.text.pdf;
using iTextSharp.text.pdf.parser;
using System.Collections.Generic;
using System;

namespace UbiSearch
{
    /// <summary>
    /// Creator : 이도형 (esrenll@gmail.com)
    /// Create : 2017.08.11
    /// LastUpdate : 2017.08.11
    /// Description : PDF 파일에서 페이지별로 파일을 읽고 단어를 검색하는 클래스
    /// Usage : Searcher 클래스 참조
    /// License : AGPL (iTextSharp), http://www.gnu.org/licenses/agpl.html
    /// </summary>
    class PdfSearcher : Searcher
    {
        public override string[] supportedExtension()
        {
            return new string[] { ".doc", ".docx" };
        }

        /// <summary>
        /// 페이지 별로 읽고 텍스트로 만들어서 반환
        /// Searcher 클래스 참조
        /// </summary>
        /// <param name="inputFilePath"></param>
        /// <returns></returns>
        protected override List<string> readByPage(string inputFilePath)
        {
            List<string> pages = new List<string>();
            PdfReader reader = new PdfReader(inputFilePath);
            for (int pageNumber = 1; pageNumber <= reader.NumberOfPages; ++pageNumber)
            {
                string page = PdfTextExtractor.GetTextFromPage(reader, pageNumber,
                    new SimpleTextExtractionStrategy());
                page += "\n";
                pages.Add(page);
            }
            return pages;
        }
    }
}
