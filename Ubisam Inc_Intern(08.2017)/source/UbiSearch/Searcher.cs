using System.Collections.Generic;

namespace UbiSearch
{
    /// <summary>
    /// Creator : 이도형 (esrenll@gmail.com)
    /// Create : 2017.08.11
    /// LastUpdate : 2017.08.30 (Info 구조체의 ToString 추가, supprotedExtension 메소드 추가)
    /// Description : 특정 파일에서 단어를 찾아 정보를 반환하는 추상 클래스
    /// Usage :  1. 클래스 생성
    ///          2. 메소드 search 로 탐색정보 반환
    /// How to make child class : 추상 메소드 readByPage 작성
    /// </summary>
    abstract class Searcher
    {
        /// <summary>
        /// 검색된 정보를 담는 구조체
        /// </summary>
        public struct Info
        {
            public string fileName;
            public int pageNum;
            public int pageLine;
            public int totalLine;
            public string refStr;
            public string searchedStr;
            public override string ToString()
            {
                string ret = "";
                ret += fileName;
                ret += "\t" + pageNum;
                ret += "\t" + pageLine;
                ret += "\t" + totalLine;
                ret += "\t" + refStr;
                ret += "\t" + searchedStr;

                return ret;
            }
            public static string toStringHeader()
            {
                string ret = "";
                ret += "FileName";
                ret += " PageNumber";
                ret += " PageLine";
                ret += " TotalLine";
                ret += " ReferencedString";
                ret += " SearchedString";

                return ret;
            }
        }
        /// <summary>
        /// 각 페이지별로 텍스트를 읽어 리스트로 반환한다.
        /// 페이지에서 각 라인은 ' '와 '\n의 조합으로 구분되어야 한다. 즉 ' \n ' 또는 ' \n' 또는 '\n '이다.
        /// '\n'만으로는 각 라인을 구분하지 못한다.
        /// 이것은 메소드 getTotalCharsInLines와 getTotalCharsInPages을 위한 것으로 위의 조건을 만족시키지 못한다면 이까지 구현하여야 한다.
        /// </summary>
        /// <param name="inputFilePath">텍스트로 변환할 파일 경로</param>
        /// <returns>각 페이지 별 텍스트</returns>
        abstract protected List<string> readByPage(string inputFilePath);

        /// <summary>
        /// 찾을 파일과 단어에 따라 공통된 로직을 실행한다.
        /// 단락이 제거된 문자열에서 해당 문자를 찾은 후,
        /// 각 페이지마다 문자가 몇개 있는지, 각 라인마다 문자가 몇개 있는지 이용하여 페이지와 라인을 찾는다.
        /// </summary>
        /// <param name="inputFilePath">찾을 파일 경로</param>
        /// <param name="searchFor">찾을 단어</param>
        /// <returns>찾은 정보의 리스트</returns>
        public List<Info> search(string inputFilePath, string searchFor)
        {
            List<string> pages = readByPage(inputFilePath);
            List<int> totalCharsInLines = getTotalCharsInLines(pages);
            List<int> totalLinesInPages = getTotalCharsInPages(pages);
            string text = "";
            foreach (string page in pages)
                text += page;
            text = text.Replace("\n", "");

            int startIdx = 0, valueIdx = -1;
            List<Info> searchedList = new List<Info>();
            string fileName = System.IO.Path.GetFileName(inputFilePath);
            while ((valueIdx = text.IndexOf(searchFor, startIdx)) >= 0)
            {
                Info newInfo = new Info();
                newInfo.fileName = fileName;
                newInfo.pageNum = totalLinesInPages.BinarySearch(valueIdx);
                newInfo.pageNum = newInfo.pageNum < 0 ? -newInfo.pageNum : newInfo.pageNum + 2;
                newInfo.totalLine = totalCharsInLines.BinarySearch(valueIdx);
                newInfo.totalLine = newInfo.totalLine < 0 ? -newInfo.totalLine : newInfo.totalLine + 2;
                int frontLines = newInfo.pageNum < 2 ? 0 : totalCharsInLines.BinarySearch(totalLinesInPages[newInfo.pageNum - 2]);
                if (frontLines < 0) frontLines = -frontLines - 1;
                newInfo.pageLine = newInfo.totalLine - frontLines;
                int subLen = searchFor.Length + 10;
                newInfo.refStr = text.Substring(valueIdx, valueIdx + subLen > text.Length ? text.Length - valueIdx : subLen);
                newInfo.searchedStr = searchFor;
                searchedList.Add(newInfo);
                startIdx = valueIdx + 1;
            }
            return searchedList;
        }
        /// <summary>
        /// 라인마다 누적 문자수가 몇인지 반환한다.
        /// 예를 들어 첫 페이지 내용이 "a\nbc\ndef \n" 이라면 {1, 3, 7}이 된다.
        /// </summary>
        /// <param name="pages">각 페이지가 가진 문자열이다. 단락은 \n으로 구분된다.</param>
        /// <returns>라인별 누적 문자수</returns>
        private List<int> getTotalCharsInLines(List<string> pages)
        {
            string text = "";
            foreach (string page in pages)
                text += page;
            List<int> totalCharsInLines = new List<int>();
            int idx = 0, cnt = 0;
            foreach (char c in text)
            {
                if (c == '\n')
                {
                    totalCharsInLines.Add(idx);
                    --idx;
                }
                else ++cnt;
                ++idx;
            }
            return totalCharsInLines;
        }
        /// <summary>
        /// 페이지마다 누적 문자 수가 몇인지 반환한다.
        /// 예를 들어 입력이 {"a\nbc", "def\ng\n", "h"} 라면 {3, 7, 8} 이다.
        /// </summary>
        /// <param name="pages">각 페이지가 가진 문자열이다. 단락은 \n으로 구분된다.</param>
        /// <returns>페이지별 누적 문자수</returns>
        private List<int> getTotalCharsInPages(List<string> pages)
        {
            List<int> totalLinesInPages = new List<int>();
            for (int pageIndex = 0; pageIndex < pages.Count; ++pageIndex)
            {
                string replaced = pages[pageIndex].Replace("\n", "");
                totalLinesInPages.Add(replaced.Length);
                if (totalLinesInPages.Count > 1)
                    totalLinesInPages[totalLinesInPages.Count - 1]
                        += totalLinesInPages[totalLinesInPages.Count - 2];
            }
            return totalLinesInPages;
        }

        abstract public string[] supportedExtension();
    }
}
