﻿#pragma checksum "..\..\fun1_DuplexPrint.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "9F8CB0E279AE689327F3A0FFC512756C"
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


namespace UbisamIntern_Project {
    
    
    /// <summary>
    /// fun1_DuplexPrint
    /// </summary>
    public partial class fun1_DuplexPrint : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        
        #line 11 "..\..\fun1_DuplexPrint.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button btnOpen;
        
        #line default
        #line hidden
        
        
        #line 14 "..\..\fun1_DuplexPrint.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button btnPrint;
        
        #line default
        #line hidden
        
        
        #line 17 "..\..\fun1_DuplexPrint.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.DataGrid dataGrid;
        
        #line default
        #line hidden
        
        
        #line 19 "..\..\fun1_DuplexPrint.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button btnOpen_Copy;
        
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
            System.Uri resourceLocater = new System.Uri("/UIP_v0.1;component/fun1_duplexprint.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\fun1_DuplexPrint.xaml"
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
            
            #line 9 "..\..\fun1_DuplexPrint.xaml"
            ((UbisamIntern_Project.fun1_DuplexPrint)(target)).KeyDown += new System.Windows.Input.KeyEventHandler(this.DuplexPrint_KeyDown);
            
            #line default
            #line hidden
            return;
            case 2:
            this.btnOpen = ((System.Windows.Controls.Button)(target));
            
            #line 11 "..\..\fun1_DuplexPrint.xaml"
            this.btnOpen.Click += new System.Windows.RoutedEventHandler(this.btnOpen_Click);
            
            #line default
            #line hidden
            return;
            case 3:
            this.btnPrint = ((System.Windows.Controls.Button)(target));
            
            #line 14 "..\..\fun1_DuplexPrint.xaml"
            this.btnPrint.Click += new System.Windows.RoutedEventHandler(this.btnPrint_Click);
            
            #line default
            #line hidden
            return;
            case 4:
            this.dataGrid = ((System.Windows.Controls.DataGrid)(target));
            
            #line 17 "..\..\fun1_DuplexPrint.xaml"
            this.dataGrid.Drop += new System.Windows.DragEventHandler(this.dataGrid_Drop);
            
            #line default
            #line hidden
            return;
            case 5:
            this.btnOpen_Copy = ((System.Windows.Controls.Button)(target));
            
            #line 19 "..\..\fun1_DuplexPrint.xaml"
            this.btnOpen_Copy.Click += new System.Windows.RoutedEventHandler(this.btnClear_Click);
            
            #line default
            #line hidden
            return;
            }
            this._contentLoaded = true;
        }
    }
}

