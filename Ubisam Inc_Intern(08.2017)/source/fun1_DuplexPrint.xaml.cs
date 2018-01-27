using Microsoft.Win32;
using System;
using System.Windows;
using System.Windows.Input;
using UbisamIntern_Project.Model;
using System.IO;
using UbiPdf;

namespace UbisamIntern_Project
{


    /// <summary>
    /// Creator : 강예진, 이도형 (esrenll@gmail.com)
    /// Create : 2017.08.15
    /// LastUpdate : 2017.08.30 (전체적인 구조 변경)
    /// Description : Fun1_DuplexPrint.xaml에 대한 상호 작용 논리
    /// License : AGPL (iTextSharp), http://www.gnu.org/licenses/agpl.html
    /// </summary>
    public partial class fun1_DuplexPrint : Window
    {
        /// <summary>
        /// dataGrid의 리스트 값들에 대한 목록
        /// </summary>
        public DuplexFileList fileList = new DuplexFileList();
        
        /// <summary>
        /// 클래스의 생성자
        /// </summary>
        public fun1_DuplexPrint()
        {
            InitializeComponent();
            dataGrid.ItemsSource = fileList;
        }

        /// <summary>
        /// Open 버튼이 클릭됐을 경우 호출
        /// 선택한 파일들을 불러온다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnOpen_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                OpenFileDialog openFileDialog = new OpenFileDialog();
                openFileDialog.Filter = "Pdf files (*.pdf)|*.pdf|All files(*)|*";
                openFileDialog.Multiselect = true;
                if (openFileDialog.ShowDialog() == true)
                {
                    insertFilesDataGrid(openFileDialog.FileNames);
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }
        }
        /// <summary>
        /// Print 버튼 클릭 시 호출
        /// PdfPrint 클래스를 이용하여 PrintDocument를 생성, 인쇄한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnPrint_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                Mouse.OverrideCursor = Cursors.Wait;
                var prgDlg = new Progress_Dialog("Convert PDF to Print Document...");
                prgDlg.ProgressModel.TotalFileNum = fileList.Count;
                foreach (var file in fileList)
                {
                    prgDlg.ProgressModel.TotalFileSize += new FileInfo(file.Name).Length;
                }
                prgDlg.Show();
                PdfPrint pdfPrint = new PdfPrint();
                for (int i = 0; i < fileList.Count; ++i)
                {
                    prgDlg.ProgressModel.CurrentFileNum = i + 1;
                    prgDlg.ProgressModel.CurrentFileSize = new FileInfo(fileList[i].Name).Length;
                    pdfPrint.insertDocument(fileList[i].Name, 96, prgDlg.ProgressModel);
                }
                prgDlg.Close();
                System.Windows.Forms.PrintDialog printDialog = new System.Windows.Forms.PrintDialog();
                printDialog.Document = pdfPrint.createPrintDocument(PdfPrint.Option.DEFAULT);
                if (printDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    printDialog.Document.Print();
                }
            }
            catch (DllNotFoundException exception)
            {
                Model.ExceptionMessageBoxTemplate.showGhostscriptDllNotFound(exception);
            }
            catch (Ghostscript.NET.GhostscriptException exception)
            {
                Model.ExceptionMessageBoxTemplate.showGhostscriptOnlySupportedEnglishPath(exception);
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }
            finally
            {
                Mouse.OverrideCursor = null;
            }
        }
        /// <summary>
        /// Clear 버튼을 누를 시 호출
        /// DataGrid의 리스트를 초기화한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnClear_Click(object sender, RoutedEventArgs e)
        {
            fileList.Clear();
        }
        /// <summary>
        /// 각각의 button의 핫키 부여
        /// 핫키 입력시 각각의 기능 수행
        /// </summary>
        private void DuplexPrint_KeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (e.Key == Key.O)
            {
                btnOpen_Click(null, null);
            }
            else if (e.Key == Key.C)
            {
                btnClear_Click(null, null);
            }
            else if (e.Key == Key.P)
            {
                btnPrint_Click(null, null);
            }
            else if (e.Key == Key.Escape)
            {
                Close();
            }
        }

        /// <summary>
        /// DataGrid에 드래그앤드롭 시 호출
        /// 해당 파일 리스트(디렉토리는 하위폴더의 모든 파일)들을 불러온다.
        /// 단 확장자를 제한한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void dataGrid_Drop(object sender, DragEventArgs e)
        {
            try
            {
                if (e.Data.GetDataPresent(DataFormats.FileDrop))
                {
                    string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);
                    insertFilesDataGrid(files);
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }
        }

        /// <summary>
        /// 해당 파일들을 DataGrid에 삽입한다.
        /// 디렉토리가 포함될 시 하위 파일들, 하위 디렉토리의 파일들을 삽입한다.
        /// 확장자를 검사한다.
        /// </summary>
        /// <param name="files"></param>
        private void insertFilesDataGrid(string[] files)
        {
            try
            {
                Mouse.OverrideCursor = Cursors.Wait;

                foreach (string file in FileExplorer.filesAndInSubDirectoryFiles(files))
                {
                    if (Path.GetExtension(file) != ".pdf") continue;
                    bool broken = false;
                    foreach (var imported in fileList)
                    {
                        if (imported.Name.Equals(file))
                        {
                            broken = true;
                            break;
                        }
                    }
                    if (broken) continue;

                    DuplexFileInfo newFile = new DuplexFileInfo();
                    newFile.Name = file;
                    FileInfo fileInfo = new FileInfo(file);
                    newFile.Modified = fileInfo.LastWriteTime.ToString();
                    newFile.Page = "" + new iTextSharp.text.pdf.PdfReader(file).NumberOfPages;
                    newFile.Size = bytesToString(fileInfo.Length);
                    fileList.Add(newFile);
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }
            finally
            {
                Mouse.OverrideCursor = null;
            }
        }

        /// <summary>
        /// bytes를 적절한 문자열로 변환한다.
        /// </summary>
        /// <param name="byteCount"></param>
        /// <returns></returns>
        public static String bytesToString(long byteCount)
        {
            string[] suf = { "B", "KB", "MB", "GB", "TB", "PB", "EB" }; //Longs run out around EB
            if (byteCount == 0)
                return "0" + suf[0];
            long bytes = Math.Abs(byteCount);
            int place = Convert.ToInt32(Math.Floor(Math.Log(bytes, 1024)));
            double num = Math.Round(bytes / Math.Pow(1024, place), 1);
            return (Math.Sign(byteCount) * num).ToString() + suf[place];
        }
    }
}
