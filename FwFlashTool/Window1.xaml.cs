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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Reflection;

namespace FwFlashTool
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class Window1 : Window
    {
        //public static System.IO.Ports.SerialPort sp = new System.IO.Ports.SerialPort();

        public Window1()
        {
            InitializeComponent();

            try
            {
                ComPort comm = new ComPort();
                comm.ShowDialog();
            }
            catch (Exception exp)
            {
                exp.ToString();
            }

            string path = Environment.CurrentDirectory.ToString();
            
            //Read settings.txt file and update device connection info
            path = Environment.CurrentDirectory.ToString();
            string commandFilePath = path + "\\" + "at_command_list.txt";

            String[] strCmdList = null;


            if (System.IO.File.Exists(commandFilePath) == true)
            {
                strCmdList = System.IO.File.ReadAllLines(commandFilePath);
                if (strCmdList != null)
                    comboBoxATCommands.ItemsSource = strCmdList;
            }
            else
            {
                MessageBox.Show("at_command_list.txt file not found");
                this.Close();
            }

            DataContext = new ViewModel();
            
        }
        private void Click_Home(object obj, EventArgs e)
        {
            btnATCmd.IsEnabled = true;
            btnUpgrade.IsEnabled = true;
            btnHelp.IsEnabled = true;
            btnATCmd.IsEnabled = true;
            btnFlash.IsEnabled = true;

            gridHome.Visibility = Visibility.Visible;
            gridAT.Visibility = Visibility.Hidden;
            gridFlash.Visibility = Visibility.Hidden;
            gridUpgrade.Visibility = Visibility.Hidden;
            gridAbout.Visibility = Visibility.Hidden;
        }
        private void Click_Upgrade(object obj, EventArgs e)
        {
            textStatusBar.Text = "Slected Upgrade Tab";
            btnATCmd.IsEnabled = true;
            btnUpgrade.IsEnabled = false;
            btnHelp.IsEnabled = true;
            btnATCmd.IsEnabled = true;
            btnFlash.IsEnabled = true;

            gridHome.Visibility = Visibility.Hidden;
            gridAT.Visibility = Visibility.Hidden;
            gridFlash.Visibility = Visibility.Hidden;
            gridAbout.Visibility = Visibility.Hidden;
            gridUpgrade.Visibility = Visibility.Visible;
        }
        private void Click_AT(object obj, EventArgs e)
        {
            textStatusBar.Text = "Slected AT Tab";
            btnATCmd.IsEnabled = true;
            btnUpgrade.IsEnabled = true;
            btnHelp.IsEnabled = true;
            btnATCmd.IsEnabled = false;
            btnFlash.IsEnabled = true;

            gridHome.Visibility = Visibility.Hidden;
            gridUpgrade.Visibility = Visibility.Hidden;
            gridFlash.Visibility = Visibility.Hidden;
            gridAbout.Visibility = Visibility.Hidden;
            gridAT.Visibility = Visibility.Visible;


        }
        private void Click_Flash(object obj, EventArgs e)
        {

            textStatusBar.Text = "Slected Flash Tab";
            btnATCmd.IsEnabled = true;
            btnUpgrade.IsEnabled = true;
            btnHelp.IsEnabled = true;
            btnATCmd.IsEnabled = true;
            btnFlash.IsEnabled = false;

            gridFlash.Visibility = Visibility.Visible;
            gridHome.Visibility = Visibility.Hidden;
            gridUpgrade.Visibility = Visibility.Hidden;
            gridAT.Visibility = Visibility.Hidden;
            gridAbout.Visibility = Visibility.Hidden;
        }

        private void Click_About(object obj, EventArgs e)
        {
            string version = ((AssemblyFileVersionAttribute)Attribute.GetCustomAttribute(
            Assembly.GetExecutingAssembly(), typeof(AssemblyFileVersionAttribute), false)).Version;

            string compright = ((AssemblyCopyrightAttribute)Attribute.GetCustomAttribute(
            Assembly.GetExecutingAssembly(), typeof(AssemblyCopyrightAttribute), false)).Copyright;

            AboutText.Text = "Firmware Flash Tool ver#" + version + "\n" + compright;

            textStatusBar.Text = "Slected Help Tab";
            btnATCmd.IsEnabled = true;
            btnUpgrade.IsEnabled = true;
            btnHelp.IsEnabled = false;
            btnATCmd.IsEnabled = true;
            btnFlash.IsEnabled = true;

            gridFlash.Visibility = Visibility.Hidden;
            gridHome.Visibility = Visibility.Hidden;
            gridUpgrade.Visibility = Visibility.Hidden;
            gridAT.Visibility = Visibility.Hidden;
            gridAbout.Visibility = Visibility.Visible;
        }
    }
}
