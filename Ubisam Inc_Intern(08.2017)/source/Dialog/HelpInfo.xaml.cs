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

namespace UbisamIntern_Project
{
    /// <summary>
    /// HelpInfo.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class HelpInfo : Window
    {
        bool leftShiftDown = false;
        bool rightShiftDown = false;
        public HelpInfo()
        {
            InitializeComponent();
        }

        private void HelpInfo_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.Key)
            {
                case Key.LeftShift: leftShiftDown = true; break;
                case Key.RightShift: rightShiftDown = true; break;
                default: break;
            }

            if ((leftShiftDown || rightShiftDown) && (e.Key == Key.Tab))
            {
                tabControl.SelectedIndex = (tabControl.SelectedIndex + tabControl.Items.Count - 1) % tabControl.Items.Count;
            }
            else if(e.Key == Key.Tab)
            {
                tabControl.SelectedIndex = (tabControl.SelectedIndex + 1) % tabControl.Items.Count;
            }
            else if (e.Key == Key.Escape)
            {
                Close();
            }
            
        }

        

        private void HelpInfo_KeyUp(object sender, KeyEventArgs e)
        {
            switch(e.Key)
            {
                case Key.LeftShift: leftShiftDown = false; break;
                case Key.RightShift: rightShiftDown = false; break;
                default: break;
            }
        }
    }
}
