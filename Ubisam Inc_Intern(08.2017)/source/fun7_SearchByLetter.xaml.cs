using System.Windows;
using Microsoft.VisualBasic;
using Microsoft.Win32;
using UbiSearch;
using System;
using System.Windows.Input;

namespace UbisamIntern_Project
{
    /// <summary>
    /// Creator : 이도형 (esrenll@gmail.com)
    /// Create : 2017.08.08
    /// LastUpdate : 2017.08.30 (엑셀이 안깔려있는 경우 예외처리 추가)
    /// Description : Fun07_SearchByLetter.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class fun7_SearchByLetter : Window
    {
        /// <summary>
        /// 생성자
        /// </summary>
        public fun7_SearchByLetter()
        {
            try
            {
                InitializeComponent();
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }
        }

        /// <summary>
        /// Search 버튼을 클릭한 경우 호출
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnSearch_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (listBox.Items.Count == 0) return;

                string searchFor = Interaction.InputBox("Enter Text For Searching");
                if (searchFor == "") return;

                Mouse.OverrideCursor = Cursors.Wait;
                Manager searchManager = new Manager();
                foreach (string file in listBox.Items)
                    searchManager.search(file, searchFor);
                try
                {
                    searchManager.showExcel();
                }
                catch (System.Runtime.InteropServices.COMException exception)
                {
                    searchManager.showNotepad();
                    Model.ExceptionMessageBoxTemplate.showMSOfficeNotInstalledException(exception);
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
        /// Clear 버튼을 클릭한 경우 호출
        /// 선택한 파일 리스트를 초기화한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnClear_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                listBox.Items.Clear();
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }

        }

        /// <summary>
        /// Add 버튼을 클릭한 경우 호출
        /// 하나 혹은 복수의 파일을 선택한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnAdd_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                OpenFileDialog openFileDialog = new OpenFileDialog();
                openFileDialog.Multiselect = true;
                openFileDialog.Filter = "PDF files, MS Word files (*.pdf,*.doc,*.docx)|*.pdf;*.doc;*.docx";
                if (openFileDialog.ShowDialog() == true)
                {
                    foreach (string file in openFileDialog.FileNames)
                    {
                        if (!listBox.Items.Contains(file))
                            listBox.Items.Add(file);
                    }
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }

        }

        /// <summary>
        /// 입력한 파일의 listBox에 파일들을 드래그앤드롭한 경우 호출
        /// 드롭한 파일들을 리스트에 추가한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void listBox_Drop(object sender, DragEventArgs e)
        {
            try
            {
                if (e.Data.GetDataPresent(DataFormats.FileDrop))
                {
                    string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);

                    foreach (string file in Model.FileExplorer.filesAndInSubDirectoryFiles(files))
                    {
                        string ex = System.IO.Path.GetExtension(file);
                        if (ex != ".pdf" && ex != ".doc" && ex != ".docx") continue;
                        if (!listBox.Items.Contains(file))
                            listBox.Items.Add(file);
                    }
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }

        }
        /// <summary>
        /// 각각의 button의 핫키 부여
        /// 핫키 입력시 각각의 기능 수행
        /// </summary>
        private void SearchByLetter_KeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            if (e.Key == Key.A)
            {
                btnAdd_Click(null, null);
            }
            else if (e.Key == Key.C)
            {
                btnClear_Click(null, null);
            }
            else if (e.Key == Key.S)
            {
                btnSearch_Click(null, null);
            }
            else if (e.Key == Key.Escape)
            {
                Close();
            }
        }
    }

}
