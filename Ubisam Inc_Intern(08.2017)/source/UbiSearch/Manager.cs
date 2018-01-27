using System;
using System.Collections.Generic;
using System.IO;
using Excel = Microsoft.Office.Interop.Excel;
using Info = UbiSearch.Searcher.Info;

namespace UbiSearch
{
    /// <summary>
    /// Creator : 이도형 (esrenll@gmail.com)
    /// Create : 2017.08.08
    /// LastUpdate : 2017.08.30 (showText 메소드 추가)
    /// Description : Word 및 PDF에서 Searcher 클래스를 이용, 특정 단어를 찾아 정보를 출력하는 클래스
    /// Usage :  1. 클래스 생성
    ///          2. 메소드 search 로 탐색정보 축적(메소드 clear로 탐색정보 초기화 가능)
    ///          3. 파일 열기 혹은 쓰기(method showExcel / writeExcel)
    /// </summary>
    public class Manager
    {
        /// <summary>
        /// 검색 결과들을 담고 있는 리스트
        /// </summary>
        private List<Info> searchedList = new List<Info>();

        /// <summary>
        /// 검색에 사용하기 위한 객체 모음
        /// </summary>
        private List<Searcher> searchers = null;

        /// <summary>
        /// 생성자. 검색에 사용할 객체 생성
        /// </summary>
        public Manager()
        {
            searchers = new List<Searcher>();
            searchers.Add(new PdfSearcher());
            searchers.Add(new WordSearcher());
        }

        public string[] supportedExtension()
        {
            List<string> ret = new List<string>();
            foreach(Searcher searcher in searchers)
            {
                foreach(string ex in searcher.supportedExtension())
                    if(!ret.Contains(ex))
                        ret.Add(ex);
            }
            return ret.ToArray();
        }

        /// <summary>
        /// 파일의 확장자에 따라 적합한 탐색자를 생성, 탐색하여 리스트에 쌓아나간다.
        /// </summary>
        /// <param name="inputFilePath">찾을 파일 경로</param>
        /// <param name="searchFor">찾을 단어</param>
        public void search(string inputFilePath, string searchFor)
        {
            string extension = System.IO.Path.GetExtension(inputFilePath);

            foreach(Searcher searcher in searchers)
            {
                foreach(string supEx in searcher.supportedExtension())
                {
                    if(supEx == extension)
                    {
                        searchedList.AddRange(searcher.search(inputFilePath, searchFor));
                        return;
                    }
                }
            }
        }
        /// <summary>
        /// 검색 결과를 초기화
        /// </summary>
        public void clear()
        {
            searchedList.Clear();
        }

        /// <summary>
        /// 검색 기록을 메모장 파일로 생성, 보인다.
        /// </summary>
        public void showNotepad()
        {
            using (TextWriter tw = new StreamWriter("SearchedList.txt"))
            {
                tw.WriteLine(Info.toStringHeader());
                foreach (Info itemText in searchedList)
                {
                    tw.WriteLine(itemText);
                }
            }
            System.Diagnostics.Process.Start("SearchedList.txt");
        }

        /// <summary>
        /// 탐색 결과를 담는 엑셀을 생성
        /// </summary>
        /// <param name="excelApp">생성된 Application 출력(반환)</param>
        /// <param name="workBook">생성된 Workbook 출력(반환)</param>
        /// <param name="workSheet">생성된 WorkSheet 출력(반환)</param>
        private void createExcel(out Excel.Application excelApp, out Excel.Workbook workBook, out Excel.Worksheet workSheet)
        {
            excelApp = new Excel.Application();
            workBook = excelApp.Workbooks.Add();
            workSheet = workBook.Worksheets.get_Item(1) as Excel.Worksheet;

            string[] colsName = { "파일이름", "찾은단어", "관련문장", "전체 줄번호", "페이지", "페이지 줄번호" };
            for (int c = 1; c <= colsName.Length; ++c)
                workSheet.Cells[1, c] = colsName[c - 1];
            int r = 1;
            foreach (Info i in searchedList)
            {
                ++r;
                workSheet.Cells[r, 1] = i.fileName;
                workSheet.Cells[r, 2] = i.searchedStr;
                workSheet.Cells[r, 3] = i.refStr;
                workSheet.Cells[r, 4] = i.totalLine;
                workSheet.Cells[r, 5] = i.pageNum;
                workSheet.Cells[r, 6] = i.pageLine;
            }
            workSheet.Columns.AutoFit();
            Excel.Range range = workSheet.Range[workSheet.Cells[1, 1], workSheet.Cells[r, 6]];
            workSheet.ListObjects.Add(
                Excel.XlListObjectSourceType.xlSrcRange, range, Type.Missing,
                XlListObjectHasHeaders: Excel.XlYesNoGuess.xlYes).Name = "Table1";
        }
        /// <summary>
        /// 사용하던 엑셀 파일을 닫음
        /// </summary>
        /// <param name="excelApp">엑셀 Application</param>
        /// <param name="workBook">엑셀 Workbook</param>
        /// <param name="workSheet">엑셀 Worksheet</param>
        private void closeExcel(Excel.Application excelApp, Excel.Workbook workBook, Excel.Worksheet workSheet)
        {
            workBook.Close(true);
            excelApp.Quit();
            ReleaseExcelObject(workSheet);
            ReleaseExcelObject(workBook);
            ReleaseExcelObject(excelApp);
        }
        /// <summary>
        /// 검색 기록을 엑셀 파일로 생성, 파일로 저장한다.
        /// </summary>
        /// <param name="fileName">저장할 파일 이름(경로포함)</param>
        public void writeExcel(string fileName)
        {
            Excel.Application excelApp = null;
            Excel.Workbook workBook = null;
            Excel.Worksheet workSheet = null;
            createExcel(out excelApp, out workBook, out workSheet);

            workBook.SaveAs(fileName, Excel.XlFileFormat.xlWorkbookNormal);
            closeExcel(excelApp, workBook, workSheet);
        }
        /// <summary>
        /// 검색 기록을 엑셀 파일로 생성, 보인다.
        /// </summary>
        public void showExcel()
        {
            Excel.Application excelApp = null;
            Excel.Workbook workBook = null;
            Excel.Worksheet workSheet = null;
            createExcel(out excelApp, out workBook, out workSheet);

            excelApp.Visible = true;
        }
        /// <summary>
        /// 백그라운드에 실행된 엑셀 파일들을 종료하기위한 메소드
        /// </summary>
        /// <param name="obj"></param>
        private void ReleaseExcelObject(object obj)
        {
            try
            {
                if (obj != null)
                {
                    System.Runtime.InteropServices.Marshal.ReleaseComObject(obj);
                    obj = null;
                }
            }
            catch (Exception ex)
            {
                obj = null;
                throw ex;
            }
            finally
            {
                GC.Collect();
            }
        }

    }
}
