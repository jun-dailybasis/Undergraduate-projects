using System;
using System.Text;
using System.Windows;
using System.IO;
using System.Windows.Forms;
using System.Drawing.Printing;
using System.Drawing;
using Excel = Microsoft.Office.Interop.Excel;
using Word = Microsoft.Office.Interop.Word;
using System.Windows.Input;

namespace UbisamIntern_Project
{
    /// <summary>
    /// Creator : 손지훈 (jihoon647@naver.com)
    /// Create : 2017.08.16
    /// LastUpdate : 2017.08.30 (예외 처리 추가)
    /// Description : fun2_DirListAndPrint.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class fun2_DirListAndPrint : Window
    {
        public fun2_DirListAndPrint()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Opne버튼 클릭시 동작 수행
        /// Folder Browser Dialog를 실행하여 선택한 File Directory를 Listbox에 목록을 추가
        /// </summary>
        private void btnOpen_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                FolderBrowserDialog fbd = new FolderBrowserDialog();

                if (fbd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    txtPath.Text = fbd.SelectedPath;
                    listBox.Items.Clear();
                    string[] files = Directory.GetFiles(fbd.SelectedPath);
                    string[] dirs = Directory.GetDirectories(fbd.SelectedPath);

                    foreach (string file in files)
                    {
                        listBox.Items.Add(file);
                    }
                    foreach (string dir in dirs)
                    {
                        listBox.Items.Add(dir);
                    }

                }
            }
            catch (Exception exception)
            {
                System.Windows.MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }
        }

        /// <summary>
        /// Print버튼 클릭시 동작 수행
        /// Print Dialog를 실행하여 파일목록을 프린트 하고자 하는 속성창 출력
        /// </summary>
        private void btnPrint_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                System.Windows.Forms.PrintDialog pdl = new System.Windows.Forms.PrintDialog();
                DialogResult result = pdl.ShowDialog();
                if (result == System.Windows.Forms.DialogResult.OK)
                {
                    string s = "";
                    foreach (string itemValue in listBox.Items)
                    {
                        s += itemValue + "\n";
                    }

                    PrintDocument pd = new PrintDocument();
                    pd.PrinterSettings = pdl.PrinterSettings;
                    pd.PrintPage += delegate (object sender1, PrintPageEventArgs e1)
                    {
                        e1.Graphics.DrawString(s, new Font("Times New Roman", 11), new SolidBrush(System.Drawing.Color.Black), new RectangleF(30, 30, pd.DefaultPageSettings.PrintableArea.Width, pd.DefaultPageSettings.PrintableArea.Height));

                    };
                    pd.Print();
                }
            }
            catch (Exception exception)
            {
                System.Windows.MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }
        }


        /// <summary>
        /// Clipboard버튼 클릭시 동작 수행
        /// Clipboard에 파일 리스트 목록을 복사
        /// </summary>
        private void btnClipboard_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (listBox.Items.Count > 0)
                {
                    StringBuilder sb = new StringBuilder();

                    foreach (string itemValue in listBox.Items)
                    {
                        sb.AppendLine(itemValue);
                    }

                    string result = sb.ToString().TrimEnd('\n');

                    System.Windows.Forms.Clipboard.SetText(result);
                }
            }
            catch (Exception exception)
            {
                System.Windows.MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }
        }

        /// <summary>
        /// Text버튼 클릭시 동작 수행
        /// Text로 저장할 수 있는 메모장에 파일 목록을 작성
        /// </summary>
        private void btnText_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (listBox.Items.Count > 0)
                {
                    using (TextWriter tw = new StreamWriter("list.txt"))
                    {
                        foreach (string itemText in listBox.Items)
                        {
                            tw.WriteLine(itemText);

                        }
                    }
                    System.Diagnostics.Process.Start("list.txt");
                }
            }
            catch (Exception exception)
            {
                System.Windows.MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }
        }

        /// <summary>
        /// Excel버튼 클릭시 동작 수행
        /// File directory list목록을 Excel에 변환하여 출력
        /// </summary>
        private void btnExcel_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                Excel.Application app;
                Excel._Workbook book;
                Excel.Workbooks books;
                Excel.Sheets sheet;
                Excel._Worksheet wsheet;
                Excel.Range range;



                app = new Excel.Application();
                books = app.Workbooks;
                book = books.Add(System.Reflection.Missing.Value);
                sheet = book.Worksheets;
                wsheet = (Excel._Worksheet)sheet.get_Item(1);
                range = wsheet.get_Range("A1", System.Reflection.Missing.Value);

                //fill the sheet
                int listCount = listBox.Items.Count;
                range = range.get_Resize(listCount, 1);
                //Create an array.
                string[,] saRet = new string[listCount, 1];

                //Fill the array.
                for (int iRow = 0; iRow < listCount; iRow++)
                {
                    saRet[iRow, 0] = listBox.Items[iRow].ToString();
                }

                range.set_Value(System.Reflection.Missing.Value, saRet);

                app.Visible = true;
                app.UserControl = true;
                wsheet.Columns.EntireColumn.AutoFit();
            }
            catch (System.Runtime.InteropServices.COMException exception)
            {
                System.Windows.MessageBox.Show("Invalid access or MS Office is not installed. Check your enviorment and try again."
                    + "\n\n" + exception.GetType().ToString() + "\n" + exception.Message);
            }
            catch (Exception exception)
            {
                System.Windows.MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }

        }

        /// <summary>
        /// Word버튼 클릭시 동작 수행
        /// File directory list목록을 Word에 변환하여 출력
        /// </summary>
        private void btnWord_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                Word.Application wrd = new Word.Application();
                var doc = wrd.Documents.Add();
                doc.Content.Paragraphs.Add();

                object start = 0;
                object end = 0;
                Word.Range rng = doc.Range(start, end);
                foreach (string itemText in listBox.Items)
                {
                    rng.Text += itemText + "\n";

                }

                wrd.Visible = true;
            }
            catch (System.Runtime.InteropServices.COMException exception)
            {
                System.Windows.MessageBox.Show("Invalid access or MS Office is not installed. Check your enviorment and try again."
                    + "\n\n" + exception.GetType().ToString() + "\n" + exception.Message);
            }
            catch (Exception exception)
            {
                System.Windows.MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }

        }
        /// <summary>
        /// 각각의 button의 핫키 부여
        /// 핫키 입력시 각각의 기능 수행
        /// </summary>
        private void DirListAndPrint_KeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (e.Key == Key.O)
            {
                btnOpen_Click(null, null);
            }
            else if (e.Key == Key.P)
            {
                btnPrint_Click(null, null);
            }
            else if (e.Key == Key.C)
            {
                btnClipboard_Click(null, null);
            }
            else if (e.Key == Key.T)
            {
                btnText_Click(null, null);
            }
            else if (e.Key == Key.E)
            {
                btnExcel_Click(null, null);
            }
            else if (e.Key == Key.W)
            {
                btnWord_Click(null, null);
            }
            else if (e.Key == Key.Escape)
            {
                Close();
            }
        }
    }
}
