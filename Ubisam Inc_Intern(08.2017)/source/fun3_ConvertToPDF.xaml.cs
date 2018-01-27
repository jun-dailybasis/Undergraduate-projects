using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using Microsoft.WindowsAPICodePack.Dialogs;
using UbiPdf;
using Microsoft.Win32;


namespace UbisamIntern_Project
{
    /// <summary>
    /// Creator : 강예진, 이도형 (esrenll@gmail.com)
    /// Create : 2017.08.07
    /// LastUpdate : 2017.08.17
    /// Description : Fun3_ConvertToPDF.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class fun3_ConvertToPDF : Window
    {
        /// <summary>
        /// 생성자
        /// </summary>
        public fun3_ConvertToPDF()
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
        /// Convert 버튼이 클릭된 경우 호출
        /// 파일을 열고 변환 후 선택된 옵션에 따라 다시 저장한다.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnConvert_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                OpenFileDialog openFileDialog = new OpenFileDialog();
                openFileDialog.Filter = "Word Files (*.doc, *.docx)|*.doc;*.docx|All Files (*.*)|*";
                if (openFileDialog.ShowDialog() == true)
                {
                    string outputFilePath = getSavePath(openFileDialog.FileName);
                    if (outputFilePath == "")
                        return;

                    Mouse.OverrideCursor = Cursors.Wait;
                    ConvertManager converter = new ConvertManager();
                    converter.convert(openFileDialog.FileName, outputFilePath);
                    MessageBox.Show("Convert Complete!\n\nResult File: " + outputFilePath);
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
        /// 선택된 옵션과 파일 이름에 따라 저장할 경로 반환
        /// 저장할 경로가 선택되지 않을 경우 빈 문자열 반환
        /// </summary>
        /// <param name="openFileName"></param>
        /// <returns></returns>
        private string getSavePath(string openFileName)
        {
            if (radioButton_Save_Source.IsChecked == true)
                return System.IO.Path.ChangeExtension(openFileName, "pdf");
            else if (radioButton_Save_Destination.IsChecked == true)
            {
                if (textBox_Save_Destination.Text == "")
                    throw new SaveDirectoryNotSelectedException("Please select your save directory or use other method.");
                else
                    return System.IO.Path.Combine(textBox_Save_Destination.Text,
                    System.IO.Path.GetFileNameWithoutExtension(openFileName) + ".pdf");
            }
            else
            {
                SaveFileDialog saveFileDialog = new SaveFileDialog();
                saveFileDialog.Filter = "PDF Files (*.pdf)|*.pdf";
                if (saveFileDialog.ShowDialog() == true)
                    return saveFileDialog.FileName;
                else
                    return "";
            }
        }

        /// <summary>
        /// 저장할 디렉토리 텍스트박스 클릭 시 폴더 선택
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void textBox_Save_Destination_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            try
            {
                CommonOpenFileDialog dialog = new CommonOpenFileDialog();
                dialog.Title = "Select Converting Destination Folder";
                dialog.IsFolderPicker = true;

                if (dialog.ShowDialog() == CommonFileDialogResult.Ok)
                {
                    textBox_Save_Destination.Text = dialog.FileName;
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
        private void ConvertToPDF_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.C)
            {
                btnConvert_Click(null, null);
            }
            else if (e.Key == Key.Escape)
            {
                Close();
            }
        }
    }

    /// <summary>
    /// 저장할 디렉토리를 선택하지 않은 경우의 예외 클래스
    /// </summary>
    class SaveDirectoryNotSelectedException : ArgumentNullException
    {
        public SaveDirectoryNotSelectedException(string msg) : base(msg)
        { }
    }
}
