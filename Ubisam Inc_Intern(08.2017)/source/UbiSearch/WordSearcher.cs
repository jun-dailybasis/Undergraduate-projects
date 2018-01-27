using System.Collections.Generic;
using Microsoft.Office.Interop.Word;
using System;

namespace UbiSearch
{
    /// <summary>
    /// Creator : 이도형 (esrenll@gmail.com)
    /// Create : 2017.08.11
    /// LastUpdate : 2017.08.12
    /// Description : MS WORD 파일에서 페이지별로 파일을 읽고 단어를 검색하는 클래스
    /// Usage : Searcher 클래스 참조
    /// </summary>
    class WordSearcher : Searcher
    {
        public override string[] supportedExtension()
        {
            return new string[]{".doc", ".docx"};
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

            Application word = new Application();
            Document doc = new Document();
            doc = word.Documents.Open(inputFilePath);

            int pageCount = doc.ComputeStatistics(WdStatistic.wdStatisticPages);
            List<int> pageStartList = new List<int>();

            object Miss = System.Reflection.Missing.Value;
            object What = WdGoToItem.wdGoToPage;
            object Which = WdGoToDirection.wdGoToAbsolute;
            object Start;
            object End;
            object CurrentPageNumber;
            object NextPageNumber;

            for (int p = 1; p <= pageCount; p++)
            {
                CurrentPageNumber = (Convert.ToInt32(p.ToString()));
                NextPageNumber = (Convert.ToInt32((p + 1).ToString()));

                pageStartList.Add(word.Selection.GoTo(ref What, ref Which, ref CurrentPageNumber, ref Miss).Start);
            }

            int lineCount = doc.ComputeStatistics(WdStatistic.wdStatisticLines);
            What = WdGoToItem.wdGoToLine;

            string page = "";
            for (int l = 1; l <= lineCount; l++)
            {
                CurrentPageNumber = (Convert.ToInt32(l.ToString()));
                NextPageNumber = (Convert.ToInt32((l + 1).ToString()));

                Start = word.Selection.GoTo(ref What, ref Which, ref CurrentPageNumber, ref Miss).Start;
                End = word.Selection.GoTo(ref What, ref Which, ref NextPageNumber, ref Miss).End;

                if (l != 1 && pageStartList.BinarySearch((int)Start) >= 0)
                {
                    pages.Add(page);
                    page = "";
                }

                if (Convert.ToInt32(Start.ToString()) != Convert.ToInt32(End.ToString()))
                    page += doc.Range(ref Start, ref End).Text.Replace('\r', ' ') + "\n";
                else
                    page += doc.Range(ref Start).Text.Replace('\r', ' ') + "\n";
            }
            pages.Add(page);
            doc.Close();
            word.Quit();

            return pages;
        }
    }
}
