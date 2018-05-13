// Author : prasadhosad@gmail.com  
// Date : 12/05/2018
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace FwFlashTool
{
    /// <summary>
    /// Interaction logic for ComPort.xaml
    /// </summary>
    public partial class ComPort : Window
    {
        public static string comm_port = "";

        public ComPort()
        {
            InitializeComponent();
        }

        private void btnCommOk_Click(object sender, RoutedEventArgs e)
        {
            if (txtCommPort.Text != "")
            {
                comm_port = txtCommPort.Text;
                this.Close();
            }
            else
            {
                MessageBox.Show("Please enter valid COM#");
                return;
            }            
        }
       
        
    }
}
