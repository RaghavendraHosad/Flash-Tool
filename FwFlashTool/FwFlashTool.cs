// Author : prasadhosad@gmail.com  
// Date : 12/05/2018
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Net;
using System.Threading;
using System.Windows.Forms;
using System.Windows;

namespace FwFlashTool
{
    class Home
    {
        #region Members
        //serial port object
        public static SerialPort sp = new SerialPort();

        string imei;
        string model;
        string rev;
        string signal;
        string make;
        string sim;
        string battary;
        List<string> portlist = new List<string>();
        #endregion

        #region Properties
        /// <summary>
        /// 
        /// </summary>
        public string IMEI
        {
            get { return imei; }
            set { imei = value; }
        }
        public string Model
        {
            get { return model; }
            set { model = value; }
        }
        public string Rev
        {
            get { return rev; }
            set { rev = value; }
        }
        public string Signal
        {
            get { return signal; }
            set { signal = value; }
        }
        public string Make
        {
            get { return make; }
            set { make = value; }
        }
        public string Sim
        {
            get { return sim; }
            set { sim = value; }
        }
        public string Battary
        {
            get { return battary; }
            set { battary = value; }
        }
        #endregion

        #region Function
        //TODO : Add if any functions
        public void Init()
        {
            //show list of valid com ports
            foreach (string s in SerialPort.GetPortNames())
            {
                portlist.Add(s);
            }

            sp.NewLine = "\r\n";
            sp.PortName = ComPort.comm_port;   //"COM5";
            sp.BaudRate = 9600;
            sp.Parity = Parity.None;
            sp.DataBits = 8;
            sp.StopBits = StopBits.One;
            sp.Handshake = Handshake.None;
            sp.DtrEnable = true;
            sp.WriteBufferSize = 1024;

            string t = ""; int timeout = 10000; //t: response msg
            string tempStr = "";
            try
            {
                if (!sp.IsOpen) sp.Open();
                System.Threading.Thread.Sleep(200);

                sp.BaseStream.Flush();
                sp.WriteLine("AT+CGSN");
                sp.BaseStream.Flush();
                while (!((t = sp.ReadExisting()).Contains("OK")) && timeout > 0) timeout--;
                if (t != "")
                {
                    t = t.Replace("OK", " ");
                    t = t.Replace("\r", " ");
                    t = t.Replace("\n", " ");


                    tempStr = t.Trim();
                    IMEI = tempStr;
                }

                System.Threading.Thread.Sleep(200);
                sp.BaseStream.Flush();
                sp.WriteLine("AT+CGMM");
                sp.BaseStream.Flush();
                while (!((t = sp.ReadExisting()).Contains("OK")) && timeout > 0) timeout--;
                if (t != "")
                {
                    t = t.Replace("OK", " ");
                    t = t.Replace("\r", " ");
                    t = t.Replace("\n", " ");

                    tempStr = "";
                    tempStr = t.Trim();
                    Model = tempStr;
                }
                System.Threading.Thread.Sleep(200);
                sp.BaseStream.Flush();
                sp.WriteLine("AT+CSQ");
                sp.BaseStream.Flush();
                while (!((t = sp.ReadExisting()).Contains("OK")) && timeout > 0) timeout--;
                if (t != "")
                {
                    t = t.Replace("OK", " ");
                    t = t.Replace("\r", " ");
                    t = t.Replace("\n", " ");
                    t = t.Split(':')[1];

                    tempStr = "";
                    tempStr = t.Trim();
                    Battary = tempStr;
                }

                System.Threading.Thread.Sleep(200);
                sp.BaseStream.Flush();
                sp.WriteLine("AT+CGMR");
                sp.BaseStream.Flush();
                while (!((t = sp.ReadExisting()).Contains("OK")) && timeout > 0) timeout--;
                if (t != "")
                {
                    t = t.Replace("OK", " ");
                    t = t.Replace("\r", " ");
                    t = t.Replace("\n", " ");

                    tempStr = "";
                    tempStr = t.Trim();
                    Rev = tempStr;
                }

                System.Threading.Thread.Sleep(200);
                sp.BaseStream.Flush();
                sp.WriteLine("AT+CREG?");
                sp.BaseStream.Flush();
                while (!((t = sp.ReadExisting()).Contains("OK")) && timeout > 0) timeout--;
                if (t != "")
                {
                    t = t.Replace("OK", " ");
                    t = t.Replace("\r", " ");
                    t = t.Replace("\n", " ");
                    t = t.Split(':')[1];

                    tempStr = "";
                    tempStr = t.Trim();
                    Signal = tempStr;
                }

                System.Threading.Thread.Sleep(200);
                sp.BaseStream.Flush();
                sp.WriteLine("AT+CGMI");
                sp.BaseStream.Flush();
                while (!((t = sp.ReadExisting()).Contains("OK")) && timeout > 0) timeout--;
                if (t != "")
                {
                    t = t.Replace("OK", " ");
                    t = t.Replace("\r", " ");
                    t = t.Replace("\n", " ");

                    tempStr = "";
                    tempStr = t.Trim();
                    Make = tempStr;
                }

                System.Threading.Thread.Sleep(200);
                sp.BaseStream.Flush();
                sp.WriteLine("AT+CPIN?");
                sp.BaseStream.Flush();
                while (!((t = sp.ReadExisting()).Contains("OK")) && timeout > 0) timeout--;
                if (t != "")
                {
                    t = t.Replace("OK", " ");
                    t = t.Replace("\r", " ");
                    t = t.Replace("\n", " ");
                    t = t.Split(':')[1];

                    tempStr = "";
                    tempStr = t.Trim();
                    Sim = tempStr;
                }
            }
            catch (Exception ex)
            {
                System.Windows.MessageBox.Show(ex.Message);
                //Application.Exit();
            }
        }
        #endregion
    }
    public class AT
    {
        #region Members
        public string commandLine;
        public string resultText;
        public string commandHelp;
        public string statusText;
        #endregion

        #region Properties
        /// <summary>
        /// 
        /// </summary>
        public string CommandLine
        {
            get { return commandLine; }
            set { commandLine = value; }
        }

        public string StatusText
        {
            get { return statusText; }
            set { statusText = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        public string ResultText
        {
            get { return resultText; }
            set { resultText = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        public string CommandHelp
        {
            get { return commandHelp; }
            set { commandHelp = value; }
        }

        //TODO : Add if any functions
        public void RunCmd(bool bPort)
        {
            try
            {
                if (bPort == true)
                {
                    Thread.Sleep(1000);
                    Home.sp.BaseStream.Flush();
                    Home.sp.WriteLine(CommandLine);
                    Home.sp.BaseStream.Flush();
                    int timeout = 10000;
                    string t = " ", tempStr = " ";
                    while (!((t = Home.sp.ReadExisting()).Contains("OK")) && timeout > 0) timeout--;
                    if (t != "")
                    {
                        t = t.Replace("OK", " ");
                        t = t.Replace("\r", " ");
                        t = t.Replace("\n", " ");

                        tempStr = "";
                        tempStr = t.Trim();
                        ResultText = tempStr;
                    }
                }
            }
            catch (Exception excp)
            {
                System.Windows.MessageBox.Show(excp.ToString());
            }
        }

        #endregion
    }
    class Flash
    {
        #region Members
        public string filePath;
        public string statusText;
        #endregion

        #region Properties
        /// <summary>
        /// The RootMcfgPath.
        /// </summary>
        public string FlashFile
        {
            get { return filePath; }
            set { filePath = value; }
        }

        /// <summary>
        /// 
        /// </summary>
        public string StatusBarText
        {
            get { return statusText; }
            set { statusText = value; }
        }

        //TODO : Add if any functions
        public bool FlashOnDevice(string model)
        {
            bool result = false;
            try
            {
                ConcreteFlashCreator objFlash = new ConcreteFlashCreator();
                FlashCls obj = objFlash.FlashFactoryMethod(model);
                obj.StubFlash();
            }
            catch (Exception expt)
            {
                System.Windows.MessageBox.Show("Device flash failed!", expt.ToString());
                result = false;
            }
            return result;
        }
        #endregion
    }

    class Upgrade
    {
        #region Members
        private bool bDlCmptl = false;
        WebClient webClient;
        public string sAppDataPath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);
        public string urlAddress = "s3.amazonaws.com//";
        public string fwInputFileToDownload;
        public string statusText;
        #endregion

        #region Properties
        /// <summary>
        /// 
        /// </summary>
        /// 
        public string UpgradeFileDownload
        {
            get { return fwInputFileToDownload; }
            set { fwInputFileToDownload = value; }
        }

        public string StatusBarText
        {
            get { return statusText; }
            set { statusText = value; }
        }

        //TODO : Add if any functions
        public void DeviceFWUpgrade(string model)
        {
            //This function initiates the filedownload after version compare
            //downloads latest file
            //path : <Folder_Name_ On_AWS><model#><file_name>
            DownloadFirmwareFile(UpgradeFileDownload);

            while (!bDlCmptl)
            {
                System.Windows.Forms.Application.DoEvents();
            }

            Thread.Sleep(2000);
        }

        //
        private void DownloadFirmwareFile(string FwFileOnAws)
        {
            if (FwFileOnAws != "")
            {

                // WebClient that will be doing the downloading for us
                using (webClient = new WebClient())
                {
                    try
                    {
                        // The variable that will be holding the url address (making sure it starts with http://)
                        Uri URL = urlAddress.StartsWith("http://", StringComparison.OrdinalIgnoreCase) ? new Uri("s3.amazonaws.com") : new Uri("https://" + "s3.amazonaws.com/" + FwFileOnAws);
                        string app_path = sAppDataPath.Replace("Roaming", "Local") + "\\" + FwFileOnAws;
                        // Start downloading the file
                        //ProgressBarText = "Downloading firmware file is in progress...";
                        //worker.ReportProgress(0, state);
                        webClient.DownloadFile(URL, app_path);
                        MessageBoxResult confirm;
                        webClient.Dispose();
                        if (System.IO.File.Exists(app_path) == true)
                        {
                            confirm = System.Windows.MessageBox.Show("File download is successful\n Would you like to upgrade device?", "Confirm", MessageBoxButton.YesNo);
                            if (confirm == MessageBoxResult.Yes)
                            {
                                System.Windows.MessageBox.Show("Flashing funtion is missing!");
                            }
                            else
                            {
                                System.Windows.MessageBox.Show("Thank you!");
                            }
                        }
                    }
                    catch (Exception ex)
                    {
                        System.Windows.MessageBox.Show(ex.Message);
                    }
                }
            }
            else
            {
                System.Windows.MessageBox.Show("Please enter valid Path");
            }

        }

        #endregion
    }

    class Help
    {
        #region Members

        #endregion

        #region Properties
        /// <summary>
        /// 
        /// </summary>

        //TODO : Add if any functions
        #endregion
    }

    interface FlashCls
    {
        bool StubFlash();
    }

    class FlashDeviceX : FlashCls
    {
        public bool StubFlash() { System.Windows.MessageBox.Show("StubFlash()\nModel# : DeviceX. \nCalled Flashing DeviceX...", "StubFlash"); return true; }
    }

    class FlashDeviceY : FlashCls
    {
        public bool StubFlash() { System.Windows.MessageBox.Show("StubFlash()\nModel# : DeviceY. \nCalled Flashing DeviceY...", "StubFlash"); return true; }
    }

    class FlashDeviceZ : FlashCls
    {
        public bool StubFlash() { System.Windows.MessageBox.Show("StubFlash()\nModel# : DeviceZ. \nCalled Flashing DeviceZ...", "StubFlash"); return true; }
    }

    abstract class FlashTypeCreator
    {
        public abstract FlashCls FlashFactoryMethod(string deviceType);
    }

    class ConcreteFlashCreator : FlashTypeCreator
    {
        public override FlashCls FlashFactoryMethod(string deviceType)
        {
            switch (deviceType)
            {
                case "DeviceX": return new FlashDeviceX();
                case "DeviceY": return new FlashDeviceY();
                case "DeviceZ": return new FlashDeviceZ();
                default: throw new ArgumentException("Invalid devicetype", deviceType);
            }
        }
    }
}
