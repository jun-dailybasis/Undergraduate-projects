using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using UbisamIntern_Project.Model;

namespace UbisamIntern_Project
{
    /// <summary>
    /// Creator : 방준영 (iris0126@kut.ac.kr)
    /// Create : 2017.08.10
    /// LastUpdate : 2017.08.17
    /// Description : 다수 파일 이름들을 일괄적 변경
    /// </summary>
    public partial class fun5_Rename : Window
    {
        /// 기존 파일 정보 Collection
        /// 바뀔 파일 정보 Collection
        /// 백업용 List
        public Model.PdfFileList pdfFileListBefore;
        public Model.PdfFileList pdfFileListAfter;
        public List<Model.PdfFileInfo> pdfFileListBackUp = new List<Model.PdfFileInfo>();

        /// <summary>
        /// 생성자
        /// PdfFileList클래스와 Listbox를 바인딩
        /// </summary>
        public fun5_Rename()
        {
            try
            {
                InitializeComponent();
                pdfFileListBefore = Resources["pdfFileListBefore"] as Model.PdfFileList;
                pdfFileListAfter = Resources["pdfFileListAfter"] as Model.PdfFileList;
            }
            catch (Exception e)
            {
                MessageBox.Show(e.GetType().ToString() + "\n\n" + e.Message);
            }
        }
        /// <summary>
        /// 버튼 클릭 이벤트
        /// 파일들의 이름을 저장된 경로로 일괄 변경
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnPath_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                for (int i = 0; i < listbox2.Items.Count; i++)
                {
                    pdfFileListAfter[i].Name = pdfFileListAfter[i].Path;

                }
                listbox2.Items.Refresh();
            }
            catch (Exception exception)
            {
                MessageBox.Show(e.GetType().ToString() + "\n\n" + exception.Message);
            }
        }
        /// <summary>
        /// 파일 목록에서 특정 파일 더블클릭시 발생하는 이벤트
        /// 개별적 이름 변경
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void listBox_DoubleClick(object sender, MouseButtonEventArgs e)
        {
            try
            {
                int index = this.listbox2.SelectedIndex;
                if (index != System.Windows.Forms.ListBox.NoMatches)
                {
                    if (listbox2.SelectedIndex >= 0)
                    {
                        String selectedName = pdfFileListAfter[listbox2.SelectedIndex].Name;
                        Rename_Dialog dialog = new Rename_Dialog();
                        dialog.textBox1.Text = selectedName;
                        dialog.ShowDialog();
                        if (dialog.cancelButtonWasClicked == true)
                        {
                            pdfFileListAfter[listbox2.SelectedIndex].Name = dialog.textBox1.Text;
                            listbox2.Items.Refresh();
                        }
                    }
                    else { MessageBox.Show("Choose a file, please"); }
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(e.GetType().ToString() + "\n\n" + exception.Message);
            }
        }

        /// <summary>
        /// 버튼 클릭 이벤트
        /// 파일 순번대로 숫자를 입력함
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnNumber_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                for (int i = 0; i < listbox2.Items.Count; i++)
                {
                    String fileName = pdfFileListAfter[i].Name;
                    String addNumber = (i + 1) + "_";
                    pdfFileListAfter[i].Name = addNumber.PadLeft(3, '0') + fileName;
                }
                listbox2.Items.Refresh();
            }
            catch (Exception exception)
            {
                MessageBox.Show(e.GetType().ToString() + "\n\n" + exception.Message);
            }
        }
        /// <summary>
        /// 버튼 클릭 이벤트
        /// 이름 변경 시행
        /// 왼쪽 리스트 -> 오른쪽 리스트로 이름 변경
        /// 예외) 이름 변경하지 않고 눌렀을 경우 예외처리
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnEnter_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (listbox2.Items.Count >= 0)
                {
                    for (int i = 0; i < listbox2.Items.Count; i++)
                    {
                        if (pdfFileListBefore[i].Path == pdfFileListAfter[i].Path)
                        { }
                        else
                        {
                            System.IO.File.Move(pdfFileListBefore[i].Path, pdfFileListAfter[i].Path + System.IO.Path.GetExtension(pdfFileListBefore[i].Path));
                        }
                    }
                    MessageBox.Show("Completed!");
                    this.Close();
                }
                else MessageBox.Show("There are no files to change!");
            }
            catch (Exception exception)
            {
                MessageBox.Show(e.GetType().ToString() + "\n\n" + exception.Message);
            }
        }

        /// <summary>
        /// 버튼 클릭 이벤트
        /// 선택한 파일의 index값을 -1해줌으로써 파일의 위치가 위로 이동
        /// 예외1) 파일 선택이 안된 경우
        /// 예외2) 첫번째 파일로 더이상 올라갈 수 없는 경우 return
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnUp_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                int selectedIndex = listbox2.SelectedIndex;
                if (selectedIndex <= 0) return;

                object itemBefore = listbox1.Items.GetItemAt(selectedIndex);
                object itemAfter = listbox2.SelectedItem;

                if (selectedIndex > 0)
                {
                    pdfFileListAfter.RemoveAt(selectedIndex);
                    pdfFileListBefore.RemoveAt(selectedIndex);
                    pdfFileListAfter.Insert(selectedIndex - 1, itemAfter as Model.PdfFileInfo);
                    pdfFileListBefore.Insert(selectedIndex - 1, itemBefore as Model.PdfFileInfo);
                    listbox2.SelectedIndex = selectedIndex - 1;
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(e.GetType().ToString() + "\n\n" + exception.Message);
            }
        }
        /// <summary>
        /// 버튼 클릭 이벤트
        /// 선택한 파일의 index값을 +1해줌으로써 파일의 위치가 위로 이동
        /// 예외1) 마지막 파일로 더이상 내려갈 수 없는 경우 return
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDown_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                int selectedIndex = listbox2.SelectedIndex;
                if (selectedIndex == listbox2.Items.Count - 1) return;

                object itemBefore = listbox1.Items.GetItemAt(selectedIndex);
                object itemAfter = listbox2.SelectedItem;
                if (selectedIndex < listbox2.Items.Count - 1)
                {
                    pdfFileListAfter.RemoveAt(selectedIndex);
                    pdfFileListBefore.RemoveAt(selectedIndex);
                    pdfFileListAfter.Insert(selectedIndex + 1, itemAfter as Model.PdfFileInfo);
                    pdfFileListBefore.Insert(selectedIndex + 1, itemBefore as Model.PdfFileInfo);
                    listbox2.SelectedIndex = selectedIndex + 1;
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(e.GetType().ToString() + "\n\n" + exception.Message);
            }
        }
        /// <summary>
        /// 버튼 클릭 이벤트
        /// 파일 이름 앞에 특정 텍스트를 추가
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnLetter_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                Rename_Dialog dialog = new Rename_Dialog();
                dialog.Title = "Add Word";
                dialog.textBox2.Text = "* Write the word you want to add";
                dialog.Show();

                dialog.Closed += delegate (object s, System.EventArgs ea)
                {
                    String addText = dialog.textBox1.Text;
                    if (dialog.enterButtonWasClicked)
                    {
                        for (int i = 0; i < listbox2.Items.Count; i++)
                        {
                            pdfFileListAfter[i].Name = addText + pdfFileListAfter[i].Name;

                        }
                        listbox2.Items.Refresh();
                        dialog.cancelButtonWasClicked = false;
                    }
                    else if (dialog.cancelButtonWasClicked) { dialog.cancelButtonWasClicked = false; }

                };
            }
            catch (Exception exception)
            {
                MessageBox.Show(e.GetType().ToString() + "\n\n" + exception.Message);
            }
        }
        /// <summary>
        /// 버튼 클릭 이벤트
        /// 처음 파일들을 담은 때로 reset
        /// 백업용 List를 사용하여 복원
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnReset_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                pdfFileListBefore.Clear();
                pdfFileListAfter.Clear();
                for (int i = 0; i < pdfFileListBackUp.Count; i++)
                {
                    pdfFileListBefore.Add(new Model.PdfFileInfo(pdfFileListBackUp[i].Path, true));
                    pdfFileListAfter.Add(new Model.PdfFileInfo(pdfFileListBackUp[i].Path, true));
                }
                listbox2.Items.Refresh();
            }
            catch (Exception exception)
            {
                MessageBox.Show(e.GetType().ToString() + "\n\n" + exception.Message);
            }
        }
        /// <summary>
        /// 파일들을 Drag & Drop 했을 때 이벤트
        /// 윈도우에서 사용자가 원하는 파일들을 선택하여 Drag&Drop으로 추가
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
                        for (int i = 0; i < listbox2.Items.Count; i++)
                        {
                            // MessageBox.Show(listbox2.Items.GetItemAt(i).ToString()+ "\n" + file);            
                            if (pdfFileListBackUp[i].Path == file)
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
                            pdfFileListBackUp.Add(new Model.PdfFileInfo(file, true));
                            pdfFileListBefore.Add(new Model.PdfFileInfo(file, true));
                            pdfFileListAfter.Add(new Model.PdfFileInfo(file, true));
                        }
                    }
                    listbox1.Items.Refresh();
                    listbox2.Items.Refresh();
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(e.GetType().ToString() + "\n\n" + exception.Message);
            }
        }
        /// <summary>
        /// 버튼 클릭 이벤트
        /// OpenFileDialog를 이용하여 파일을 추가
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnOpen_Click(object sender, RoutedEventArgs e)
        {
            bool checkBreak = false;
            try
            {
                Microsoft.Win32.OpenFileDialog dialog = new Microsoft.Win32.OpenFileDialog();
                dialog.Multiselect = true;
                dialog.ShowDialog();
                foreach (string file in FileExplorer.filesAndInSubDirectoryFiles(dialog.FileNames))
                {
                    // MessageBox.Show(listbox2.Items.GetItemAt(i).ToString() + "\n" + file.Split('\\').Last());
                    for (int i = 0; i < listbox2.Items.Count; i++)
                    {
                        // MessageBox.Show(listbox2.Items.GetItemAt(i).ToString()+ "\n" + file);            
                        if (pdfFileListBackUp[i].Path == file)
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
                        pdfFileListBackUp.Add(new Model.PdfFileInfo(file, true));
                        pdfFileListBefore.Add(new Model.PdfFileInfo(file, true));
                        pdfFileListAfter.Add(new Model.PdfFileInfo(file, true));
                    }
                }
                listbox1.Items.Refresh();
                listbox2.Items.Refresh();
            }
            catch (Exception exception)
            {
                MessageBox.Show(e.GetType().ToString() + "\n\n" + exception.Message);
            }
        }

        /// <summary>
        /// 버튼 클릭 이벤트
        /// List를 모두 비움
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnClear_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                pdfFileListBackUp.Clear();
                pdfFileListBefore.Clear();
                pdfFileListAfter.Clear();

                listbox1.Items.Refresh();
                listbox2.Items.Refresh();
                CannotClickBtns();
                Keyboard.ClearFocus();
            }
            catch (Exception exception)
            {
                MessageBox.Show(e.GetType().ToString() + "\n\n" + exception.Message);
            }

        }
        /// <summary>
        /// 버튼 클릭 이벤트
        /// 특정 문자열을 제거
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDelete_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                Rename_Dialog dialog = new Rename_Dialog();
                dialog.Title = "Remove Word";
                dialog.textBox2.Text = "* Write the word you want to delete";
                dialog.Show();

                dialog.Closed += delegate (object s, System.EventArgs ea)
                {

                    String wordBefore = dialog.textBox1.Text;
                    if (dialog.enterButtonWasClicked)
                    {
                        for (int i = 0; i < listbox2.Items.Count; i++)
                        {
                            pdfFileListAfter[i].Name = pdfFileListAfter[i].Name.Replace(wordBefore, "");

                        }
                        listbox2.Items.Refresh();
                        dialog.cancelButtonWasClicked = false;
                    }
                    else if (dialog.cancelButtonWasClicked) { dialog.cancelButtonWasClicked = false; }

                };
                Keyboard.ClearFocus();
            }
            catch (Exception exception)
            {
                MessageBox.Show(e.GetType().ToString() + "\n\n" + exception.Message);
            }
        }
        /// <summary>
        /// 버튼 클릭 이벤트
        /// 특정 문자열을 원하는 문자열로 변경
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnChange_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                WordChange_Dialog dialog = new WordChange_Dialog();
                dialog.Show();


                dialog.Closed += delegate (object s, System.EventArgs ea)
                {
                    String wordBefore = dialog.textBox1.Text;
                    String wordAfter = dialog.textBox2.Text;

                    if (dialog.enterButtonWasClicked)
                    {
                        if ((dialog.textBox1.Text.Equals("") || dialog.textBox2.Text.Equals("")))
                            MessageBox.Show("Error: write text.");
                        else
                        {
                            for (int i = 0; i < listbox2.Items.Count; i++)
                            {
                                pdfFileListAfter[i].Name = pdfFileListAfter[i].Name.Replace(wordBefore, wordAfter);

                            }
                            listbox2.Items.Refresh();
                            dialog.enterButtonWasClicked = false;
                        }
                    }
                    else if (dialog.cancelButtonWasClicked) { dialog.cancelButtonWasClicked = false; }

                };
            }
            catch (Exception exception)
            {
                MessageBox.Show(e.GetType().ToString() + "\n\n" + exception.Message);
            }
        }
     
        /// <summary>
        /// ListBox가 업데이트 될때 마다 불러오는 함수
        /// 비어있는지 아닌지를 판별하여 버튼들의 활성화 유무를 판단
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void listbox_Updated(object sender, EventArgs e)
        {
            try
            {
                if (listbox2.Items.IsEmpty) CannotClickBtns();
                if (listbox2.Items.Count > 0) CanClickBtns();
            }
            catch (Exception exception)
            {
                MessageBox.Show(e.GetType().ToString() + "\n\n" + exception.Message);
            }
        }
        /// <summary>
        /// 버튼 활성화
        /// </summary>
        private void CanClickBtns()
        {
            btnPath.IsEnabled = true;
            btnNumber.IsEnabled = true;
            btnLetter.IsEnabled = true;
            btnEnter.IsEnabled = true;
            btnReset.IsEnabled = true;
            btnDelete.IsEnabled = true;
            btnUp.IsEnabled = true;
            btnDown.IsEnabled = true;
            btnClear.IsEnabled = true;
            btnChange.IsEnabled = true;


            btnPath.Foreground = Brushes.White;
            btnPath.Background = Brushes.Black;
            btnNumber.Foreground = Brushes.White;
            btnNumber.Background = Brushes.Black;
            btnLetter.Foreground = Brushes.White;
            btnLetter.Background = Brushes.Black;
            btnEnter.Foreground = Brushes.White;
            btnEnter.Background = Brushes.Black;
            btnReset.Foreground = Brushes.White;
            btnReset.Background = Brushes.Black;
            btnDelete.Foreground = Brushes.White;
            btnDelete.Background = Brushes.Black;
            btnUp.Foreground = Brushes.White;
            btnUp.Background = Brushes.Black;
            btnDown.Foreground = Brushes.White;
            btnDown.Background = Brushes.Black;
            btnClear.Foreground = Brushes.White;
            btnClear.Background = Brushes.Black;
            btnChange.Foreground = Brushes.White;
            btnChange.Background = Brushes.Black;
        }
        /// <summary>
        /// 버튼 비활성화
        /// </summary>
        private void CannotClickBtns()
        {
            btnPath.IsEnabled = false;
            btnNumber.IsEnabled = false;
            btnLetter.IsEnabled = false;
            btnEnter.IsEnabled = false;
            btnReset.IsEnabled = false;
            btnDelete.IsEnabled = false;
            btnUp.IsEnabled = false;
            btnDown.IsEnabled = false;
            btnClear.IsEnabled = false;
            btnChange.IsEnabled = false;
            btnPath.Foreground = Brushes.Gray;
            btnPath.Background = Brushes.LightGray;
            btnNumber.Foreground = Brushes.Gray;
            btnNumber.Background = Brushes.LightGray;
            btnLetter.Foreground = Brushes.Gray;
            btnLetter.Background = Brushes.LightGray;
            btnEnter.Foreground = Brushes.Gray;
            btnEnter.Background = Brushes.LightGray;
            btnReset.Foreground = Brushes.Gray;
            btnReset.Background = Brushes.LightGray;
            btnDelete.Foreground = Brushes.Gray;
            btnDelete.Background = Brushes.LightGray;
            btnUp.Foreground = Brushes.Gray;
            btnUp.Background = Brushes.LightGray;
            btnDown.Foreground = Brushes.Gray;
            btnDown.Background = Brushes.LightGray;
            btnClear.Foreground = Brushes.Gray;
            btnClear.Background = Brushes.LightGray;
            btnChange.Foreground = Brushes.Gray;
            btnChange.Background = Brushes.LightGray;
        }
        /// <summary>
        /// 각각의 button의 핫키 부여
        /// 핫키 입력시 각각의 기능 수행
        /// </summary>
        private void Rename_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.O)
            {
                btnOpen_Click(null, null);
            }
            else if (e.Key == Key.C)
            {
                btnClear_Click(null, null);
            }
            else if (e.Key == Key.R)
            {
                btnReset_Click(null, null);
            }
            else if (e.Key == Key.P)
            {
                btnPath_Click(null, null);
            }
            else if (e.Key == Key.N)
            {
                btnNumber_Click(null, null);
            }
            else if (e.Key == Key.L)
            {
                btnLetter_Click(null, null);
            }
            else if (e.Key == Key.H)
            {
                btnChange_Click(null, null);
            }
            else if (e.Key == Key.D)
            {
                btnDelete_Click(null, null);
            }
            else if (e.Key == Key.Enter)
            {
                btnEnter_Click(null, null);
            }
            else if (e.Key == Key.Escape)
            {
                Close();
            }
            else if (e.Key == Key.Delete)
            {
                int selectedIndex = listbox2.SelectedIndex;
                if (e.Key == Key.Delete)
                {
                    if (listbox2.SelectedIndex != -1)
                    {
                        pdfFileListBefore.RemoveAt(listbox2.SelectedIndex);
                        pdfFileListAfter.RemoveAt(listbox2.SelectedIndex);
                        if (selectedIndex == listbox2.Items.Count) listbox2.SelectedIndex = selectedIndex - 1;
                        else if (selectedIndex < listbox2.Items.Count)
                        {
                            listbox2.SelectedIndex = selectedIndex;
                        }
                    }
                }
                listbox2.Items.Refresh();
            }
        }
    }
}
