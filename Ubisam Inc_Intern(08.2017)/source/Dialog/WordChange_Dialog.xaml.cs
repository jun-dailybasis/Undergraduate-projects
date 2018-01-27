using System.Windows;
using System.Windows.Input;

namespace UbisamIntern_Project
{
    /// <summary>
    /// Creator : 방준영 (iris0126@kut.ac.kr)
    /// Create : 2017.08.10
    /// LastUpdate : 2017.08.13
    /// Description : 파일이름내 텍스트 변경시 뜨는 창
    /// </summary>
    public partial class WordChange_Dialog : Window
    {
        /// <summary>
        /// Enter, Cancel 어떤 버튼이 클릭 됬는지 판단하기 위한 변수 2개
        /// </summary>
        public bool enterButtonWasClicked = false;
        public bool cancelButtonWasClicked = false;
        public WordChange_Dialog()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Enter Button Click Event
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnEnter_Click(object sender, RoutedEventArgs e)
        {
            enterButtonWasClicked = true;
            this.Close();
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
        /// Keyboard 입력 시
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void textbox_KeyPress(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                if (textBox1.Text.Equals("") || textBox2.Text.Equals("")) MessageBox.Show("Please, Please enter the letters.");
                else
                {
                    enterButtonWasClicked = true;
                    Close();
                }
            }
            else if (e.Key == Key.Escape)
            {
                cancelButtonWasClicked = true;
                Close();
            }
        }
        /// <summary>
        /// Keyboard 입력 시
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void WordChange_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Escape || e.Key == Key.C)
            {
                cancelBtn_Click(null, null);
            }
            else if (e.Key == Key.Enter)
            {
                btnEnter_Click(null, null);
            }
            
        }
    }
}
