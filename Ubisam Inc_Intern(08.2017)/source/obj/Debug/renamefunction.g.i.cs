﻿#pragma checksum "..\..\renamefunction.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "47C9B1F41DF0F3DE6DD146D809D26CAE"
//------------------------------------------------------------------------------
// <auto-generated>
//     이 코드는 도구를 사용하여 생성되었습니다.
//     런타임 버전:4.0.30319.42000
//
//     파일 내용을 변경하면 잘못된 동작이 발생할 수 있으며, 코드를 다시 생성하면
//     이러한 변경 내용이 손실됩니다.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;
using UbisamIntern_Project;
using UbisamIntern_Project.Model;


namespace UbisamIntern_Project {
    
    
    /// <summary>
    /// renameFunction
    /// </summary>
    public partial class renameFunction : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        
        #line 17 "..\..\renamefunction.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ListBox listbox1;
        
        #line default
        #line hidden
        
        
        #line 18 "..\..\renamefunction.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ListBox listbox2;
        
        #line default
        #line hidden
        
        
        #line 19 "..\..\renamefunction.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button downBtn;
        
        #line default
        #line hidden
        
        
        #line 20 "..\..\renamefunction.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button upBtn;
        
        #line default
        #line hidden
        
        
        #line 32 "..\..\renamefunction.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button pathBtn;
        
        #line default
        #line hidden
        
        
        #line 33 "..\..\renamefunction.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button numBtn;
        
        #line default
        #line hidden
        
        
        #line 34 "..\..\renamefunction.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button textBtn;
        
        #line default
        #line hidden
        
        
        #line 35 "..\..\renamefunction.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button resetBtn;
        
        #line default
        #line hidden
        
        
        #line 36 "..\..\renamefunction.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button okBtn;
        
        #line default
        #line hidden
        
        
        #line 37 "..\..\renamefunction.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button removeBtn;
        
        #line default
        #line hidden
        
        
        #line 38 "..\..\renamefunction.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button clearBtn;
        
        #line default
        #line hidden
        
        
        #line 39 "..\..\renamefunction.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button changedBtn;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/WpfApplication2;component/renamefunction.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\renamefunction.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.listbox1 = ((System.Windows.Controls.ListBox)(target));
            
            #line 17 "..\..\renamefunction.xaml"
            this.listbox1.Drop += new System.Windows.DragEventHandler(this.FilePanel_Drop);
            
            #line default
            #line hidden
            return;
            case 2:
            this.listbox2 = ((System.Windows.Controls.ListBox)(target));
            
            #line 18 "..\..\renamefunction.xaml"
            this.listbox2.Drop += new System.Windows.DragEventHandler(this.FilePanel_Drop);
            
            #line default
            #line hidden
            
            #line 18 "..\..\renamefunction.xaml"
            this.listbox2.MouseDoubleClick += new System.Windows.Input.MouseButtonEventHandler(this.listBox_DoubleClick);
            
            #line default
            #line hidden
            
            #line 18 "..\..\renamefunction.xaml"
            this.listbox2.KeyDown += new System.Windows.Input.KeyEventHandler(this.listbox_KeyPress);
            
            #line default
            #line hidden
            
            #line 18 "..\..\renamefunction.xaml"
            this.listbox2.LayoutUpdated += new System.EventHandler(this.listbox_Updated);
            
            #line default
            #line hidden
            return;
            case 3:
            this.downBtn = ((System.Windows.Controls.Button)(target));
            
            #line 19 "..\..\renamefunction.xaml"
            this.downBtn.Click += new System.Windows.RoutedEventHandler(this.downBtn_Click);
            
            #line default
            #line hidden
            return;
            case 4:
            this.upBtn = ((System.Windows.Controls.Button)(target));
            
            #line 20 "..\..\renamefunction.xaml"
            this.upBtn.Click += new System.Windows.RoutedEventHandler(this.upBtn_Click);
            
            #line default
            #line hidden
            return;
            case 5:
            
            #line 31 "..\..\renamefunction.xaml"
            ((System.Windows.Controls.Button)(target)).Click += new System.Windows.RoutedEventHandler(this.openBtn_Click);
            
            #line default
            #line hidden
            return;
            case 6:
            this.pathBtn = ((System.Windows.Controls.Button)(target));
            
            #line 32 "..\..\renamefunction.xaml"
            this.pathBtn.Click += new System.Windows.RoutedEventHandler(this.directoryBtn_Click);
            
            #line default
            #line hidden
            return;
            case 7:
            this.numBtn = ((System.Windows.Controls.Button)(target));
            
            #line 33 "..\..\renamefunction.xaml"
            this.numBtn.Click += new System.Windows.RoutedEventHandler(this.sequenceBtn_Click);
            
            #line default
            #line hidden
            return;
            case 8:
            this.textBtn = ((System.Windows.Controls.Button)(target));
            
            #line 34 "..\..\renamefunction.xaml"
            this.textBtn.Click += new System.Windows.RoutedEventHandler(this.textBtn_Click);
            
            #line default
            #line hidden
            return;
            case 9:
            this.resetBtn = ((System.Windows.Controls.Button)(target));
            
            #line 35 "..\..\renamefunction.xaml"
            this.resetBtn.Click += new System.Windows.RoutedEventHandler(this.resetBtn_Click);
            
            #line default
            #line hidden
            return;
            case 10:
            this.okBtn = ((System.Windows.Controls.Button)(target));
            
            #line 36 "..\..\renamefunction.xaml"
            this.okBtn.Click += new System.Windows.RoutedEventHandler(this.okbtn_Click);
            
            #line default
            #line hidden
            return;
            case 11:
            this.removeBtn = ((System.Windows.Controls.Button)(target));
            
            #line 37 "..\..\renamefunction.xaml"
            this.removeBtn.Click += new System.Windows.RoutedEventHandler(this.remoTextBtn_Click);
            
            #line default
            #line hidden
            return;
            case 12:
            this.clearBtn = ((System.Windows.Controls.Button)(target));
            
            #line 38 "..\..\renamefunction.xaml"
            this.clearBtn.Click += new System.Windows.RoutedEventHandler(this.clearBtn_Click);
            
            #line default
            #line hidden
            return;
            case 13:
            this.changedBtn = ((System.Windows.Controls.Button)(target));
            
            #line 39 "..\..\renamefunction.xaml"
            this.changedBtn.Click += new System.Windows.RoutedEventHandler(this.txtChange_Click);
            
            #line default
            #line hidden
            return;
            }
            this._contentLoaded = true;
        }
    }
}
