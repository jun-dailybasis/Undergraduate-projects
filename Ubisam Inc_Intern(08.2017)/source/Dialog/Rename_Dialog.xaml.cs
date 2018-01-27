using System.Windows;
using System.Windows.Input;

namespace UbisamIntern_Project
{
    /// <summary>
    /// Creator : 방준영 (iris0126@kut.ac.kr)
    /// Create : 2017.08.10
    /// LastUpdate : 2017.08.13
    /// Description : 다수 파일 이름을 일괄적 변경
    /// </summary>
    public partial class Rename_Dialog : Window
    {
        /// Enter, Cancel 어떤 버튼을 클릭했는지 판단하기 위한 변수
        public bool enterButtonWasClicked = false;
        public bool cancelButtonWasClicked = false;
        public Rename_Dialog()
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
            Close();
        }
        /// <summary>
        /// Keyboard 입력
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void RenameDl_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Escape )
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
