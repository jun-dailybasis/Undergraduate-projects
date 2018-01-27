using System;
using System.Windows;
using System.Windows.Input;
using Microsoft.WindowsAPICodePack.Dialogs;
namespace UbisamIntern_Project
{
    /// <summary>
    /// Creator : 방준영 (iris0126@kut.ac.kr)
    /// Create : 2017.08.10
    /// LastUpdate : 2017.08.13
    /// Description : 파일 경로 변경시 뜨는 창
    /// </summary>
    public partial class Repath_Dialog : Window
    {
        /// <summary>
        /// Enter, Cancel 어떤 버튼이 클릭 됬는지 판단하기 위한 변수 2개
        /// 바뀌게 될 최종 파일 경로를 저장하는 변수 1개
        /// </summary>
        public bool enterButtonWasClicked = false;
        public bool cancelButtonWasClicked = false;
        public String changedPath;
        public Repath_Dialog()
        {
            InitializeComponent();
        }
        /// <summary>
        /// Path버튼 클릭
        /// 폴더 경로를 반환
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnPath_Click(object sender, RoutedEventArgs e)
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
                    if (result == CommonFileDialogResult.Ok)
                    {
                        changedPath = folderSelectorDialog.FileName;
                        this.Close();

                    }
                    else if (result == CommonFileDialogResult.Cancel)
                    {
                    }
                }
                else MessageBox.Show("Dialog Result Error");
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
            }


        }
        /// <summary>
        /// Enter Button Click Event
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnEnter_Click(object sender, RoutedEventArgs e)
        {
            enterButtonWasClicked = true;
            Close();
        }
        /// <summary>
        /// Cancel Button Click Event
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cancelBtn_Click(object sender, RoutedEventArgs e)
        {
            cancelButtonWasClicked = true;
            this.Close();
        }
        /// <summary>
        /// Keyboard 입력
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void RepathDl_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Escape || e.Key == Key.C)
            {
                cancelBtn_Click(null, null);
            }
            else if (e.Key == Key.Enter)
            {
                btnEnter_Click(null, null);
            }
            else if (e.Key == Key.P)
            {
                btnPath_Click(null, null);
            }
        }
    }
}
