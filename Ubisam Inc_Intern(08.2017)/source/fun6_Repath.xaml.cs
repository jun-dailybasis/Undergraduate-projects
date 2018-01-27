using System;
using System.Windows;
using System.Windows.Input;
using Microsoft.WindowsAPICodePack.Dialogs;
using System.Windows.Media;
using UbisamIntern_Project.Model;
using System.Collections.Generic;

namespace UbisamIntern_Project
{
    /// <summary>
    /// Creator : 방준영 (iris0126@kut.ac.kr)
    /// Create : 2017.08.10
    /// LastUpdate : 2017.08.13
    /// Description : 다수 파일의 경로를 일괄적 변경
    /// </summary>
    public partial class fun6_Repath : Window
    {

        /// 기존 파일 정보 Collection
        /// 바뀔 파일 정보 Collection
        /// 파일 목적지의 경로 
        public List<Model.PdfFileInfo> pdfFileListBackup = new List<Model.PdfFileInfo>();
        public Model.PdfFileList pdfFileListAfter;
        public String destinationFile;
        public bool moveIsClicked = false;
        public bool copyIsClicked = false;
        public fun6_Repath()
        { /// <summary>
          /// 생성자 : 초기화, 바인딩
          /// </summary>
            InitializeComponent();
            radioMove.IsChecked = true;
            CannotClickBtns();
            pdfFileListAfter = Resources["pdfFileListAfter"] as Model.PdfFileList;
        }

        /// <summary>
        /// 사용자가 원하는 파일 경로를 선택
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnOpen_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                Microsoft.Win32.OpenFileDialog dialog = new Microsoft.Win32.OpenFileDialog();
                dialog.Multiselect = true;
                dialog.ShowDialog();

                foreach (String file in dialog.FileNames)
                {
                    pdfFileListBackup.Add(new Model.PdfFileInfo(file, false));
                    pdfFileListAfter.Add(new Model.PdfFileInfo(file, false));
                }
                listbox3.Items.Refresh();
                CanClickBtns();
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }

        }
        /// <summary>
        /// 파일 목록에서 특정 파일 더블클릭
        /// 개별적 경로 변경
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void listBox_DoubleClick(object sender, MouseButtonEventArgs e)
        {
            try
            {
                int selectedindex = this.listbox3.SelectedIndex;
                if (selectedindex != System.Windows.Forms.ListBox.NoMatches)
                {
                    if (listbox3.SelectedIndex >= 0)
                    {
                        Repath_Dialog dialog = new Repath_Dialog();
                        dialog.ShowDialog();
                        if (dialog.cancelButtonWasClicked)
                        {
                            dialog.cancelButtonWasClicked = false;
                        }
                        else if (dialog.changedPath != "")
                        {
                            destinationFile = dialog.changedPath;
                            pdfFileListAfter[selectedindex].Path = destinationFile + "\\" + pdfFileListAfter[selectedindex].Name;
                            dialog.enterButtonWasClicked = false;
                            listbox3.Items.Refresh();
                        }
                       
                        else MessageBox.Show("Dialog Error");
                    }
                    else { MessageBox.Show("Please, Select file.."); }
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }

        }
        /// <summary>
        /// 경로 변경 시행
        /// 왼쪽 리스트 -> 오른쪽 리스트로 경로 변경
        /// 예외 1) 경로름 변경하지 않았을 경우 예외처리
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnEnter_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (moveIsClicked)
                {
                    for (int i = 0; i < listbox3.Items.Count; i++)
                    {
                        if (pdfFileListBackup[i].Path != pdfFileListAfter[i].Path)
                        {
                            System.IO.File.Move(pdfFileListBackup[i].Path, pdfFileListAfter[i].Path);
                        }
                        else
                        { }
                    }
                    MessageBox.Show("Completed!");
                    this.Close();
                }

                else if (copyIsClicked)
                {
                    for (int i = 0; i < listbox3.Items.Count; i++)
                    {
                        if (pdfFileListBackup[i].Path != pdfFileListAfter[i].Path)
                        {
                            System.IO.File.Copy(pdfFileListBackup[i].Path, pdfFileListAfter[i].Path);
                        }
                        else
                        { }
                    }
                    MessageBox.Show("Completed!");
                    this.Close();
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }
        }
        /// <summary>
        /// 선택한 파일들을 동일한 경로로 옮기고자 할 경우
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnOnepath_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (CommonFileDialog.IsPlatformSupported)
                {

                    var folderSelectorDialog = new CommonOpenFileDialog();
                    folderSelectorDialog.EnsureReadOnly = true;
                    folderSelectorDialog.IsFolderPicker = true;
                    folderSelectorDialog.AllowNonFileSystemItems = false;
                    folderSelectorDialog.Multiselect = false;
                    folderSelectorDialog.Title = "Project Location";
                    CommonFileDialogResult result = folderSelectorDialog.ShowDialog();
                    if (result == CommonFileDialogResult.Cancel) { }
                    else if (result == CommonFileDialogResult.Ok && folderSelectorDialog.FileName != "")
                    {
                        for (int i = 0; i < listbox3.Items.Count; i++)
                        {
                            pdfFileListAfter[i].Path = folderSelectorDialog.FileName + "\\" + pdfFileListAfter[i].Name;
                        }
                    }
                    else MessageBox.Show("Dialog Result Error");

                    listbox3.Items.Refresh();
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }
        }

        /// <summary>
        /// 사용자가 원하는 파일을 List에 표시
        /// Drag & Drop 형태로 불러옴
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FilePanel_Drop(object sender, DragEventArgs e)
        {
            bool checkBreak = false;
            try
            {
                if (e.Data.GetDataPresent(DataFormats.FileDrop))
                {
                    // Note that you can have more than one file.
                    string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);

                    // Assuming you have one file that you care about, pass it off to whatever
                    // handling code you have defined.

                    foreach (string file in FileExplorer.filesAndInSubDirectoryFiles(files))
                    {
                        // MessageBox.Show(listbox2.Items.GetItemAt(i).ToString() + "\n" + file.Split('\\').Last());
                        for (int i = 0; i < listbox3.Items.Count; i++)
                        {
                            // MessageBox.Show(listbox2.Items.GetItemAt(i).ToString()+ "\n" + file);            
                            if (pdfFileListBackup[i].Path == file)
                            {
                                checkBreak = true;
                                break;
                            }
                        }
                        if (checkBreak == true)
                        {
                            checkBreak = false;
                            continue;
                        }
                        else
                        {
                            pdfFileListBackup.Add(new Model.PdfFileInfo(file, false));
                            pdfFileListAfter.Add(new Model.PdfFileInfo(file, false));
                        }
                    }
                    listbox3.Items.Refresh();
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(e.GetType().ToString() + "\n\n" + exception.Message);
            }
        }
        /// <summary>
        /// 각각의 button의 핫키 부여
        /// 핫키 입력시 각각의 기능 수행
        /// </summary>
        private void Repath_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.O)
            {
                btnOpen_Click(null, null);
            }
            else if (e.Key == Key.P)
            {
                btnOnepath_Click(null, null);
            }
            else if (e.Key == Key.Escape)
            {
                Close();
            }
        }
        /// <summary>
        /// 버튼 활성화
        /// </summary>
        private void CanClickBtns()
        {
            btnOne.IsEnabled = true;
            btnEnter.IsEnabled = true;
            btnOne.Foreground = Brushes.White;
            btnOne.Background = Brushes.Black;
            btnEnter.Foreground = Brushes.White;
            btnEnter.Background = Brushes.Black;
        }
        /// <summary>
        /// 버튼 비활성화
        /// </summary>
        private void CannotClickBtns()
        {
            btnOne.IsEnabled = false;
            btnEnter.IsEnabled = false;
            btnOne.Foreground = Brushes.Gray;
            btnOne.Background = Brushes.LightGray;
            btnEnter.Foreground = Brushes.Gray;
            btnEnter.Background = Brushes.LightGray;
        }

        private void radioCopy_Checked(object sender, RoutedEventArgs e)
        {
            moveIsClicked = true;
        }

        private void RadioButton_Checked(object sender, RoutedEventArgs e)
        {
            copyIsClicked = true;
        }

        private void listbox_Update(object sender, EventArgs e)
        {
            {
                try
                {
                    if (listbox3.Items.IsEmpty) CannotClickBtns();
                    if (listbox3.Items.Count > 0) CanClickBtns();
                }
                catch (Exception exception)
                {
                    MessageBox.Show(e.GetType().ToString() + "\n\n" + exception.Message);
                }
            }
        }
    }
}
