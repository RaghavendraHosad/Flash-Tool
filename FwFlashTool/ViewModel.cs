// Author : prasadhosad@gmail.com  
// Date : 12/05/2018
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Input;
using MicroMvvm;

namespace FwFlashTool
{
    class ViewModel : ObservableObject
    {
        #region Construction
        /// <summary>
        /// Constructs the default instance of a PriMcfgOneViewModel
        /// </summary>
        public ViewModel()
        {
            _at = new AT { };
            _home = new Home { };
            _flash = new Flash { };
            _upgrade = new Upgrade { };
            _home.Init();
        }
        #endregion

        #region Members
        AT _at;
        Home _home;
        Flash _flash;
        Upgrade _upgrade;
        #endregion

        #region Properties
        public AT AT
        {
            get
            {
                return _at;
            }
            set
            {
                _at = value;
            }
        }
        public Home Home
        {
            get
            {
                return _home;
            }
            set
            {
                _home = value;
            }
        }

        public Flash Flash
        {
            get
            {
                return _flash;
            }
            set
            {
                _flash = value;
            }
        }


        public Upgrade Upgrade
        {
            get
            {
                return _upgrade;
            }
            set
            {
                _upgrade = value;
            }
        }

        public string IMEI
        {
            get { return Home.IMEI; }
            set
            {
                if (Home.IMEI != value)
                {
                    Home.IMEI = value;
                    RaisePropertyChanged("IMEI");
                }
            }
        }

        public string Model
        {
            get { return Home.Model; }
            set
            {
                if (Home.Model != value)
                {
                    Home.Model = value;
                    RaisePropertyChanged("Model");
                }
            }
        }

        public string Rev
        {
            get { return Home.Rev; }
            set
            {
                if (Home.Rev != value)
                {
                    Home.Rev = value;
                    RaisePropertyChanged("Rev");
                }
            }
        }

        public string Signal
        {
            get { return Home.Signal; }
            set
            {
                if (Home.Signal != value)
                {
                    Home.Signal = value;
                    RaisePropertyChanged("Signal");
                }
            }
        }

        public string Make
        {
            get { return Home.Make; }
            set
            {
                if (Home.Make != value)
                {
                    Home.Make = value;
                    RaisePropertyChanged("Make");
                }
            }
        }

        public string Sim
        {
            get { return Home.Sim; }
            set
            {
                if (Home.Sim != value)
                {
                    Home.Sim = value;
                    RaisePropertyChanged("Sim");
                }
            }
        }

        public string Battary
        {
            get { return Home.Battary; }
            set
            {
                if (Home.Battary != value)
                {
                    Home.Battary = value;
                    RaisePropertyChanged("Battary");
                }
            }
        }

        public string CommandLine
        {
            get { return AT.CommandLine; }
            set
            {
                if (AT.CommandLine != value)
                {
                    AT.CommandLine = value;
                    RaisePropertyChanged("CommandLine");
                }
            }
        }

        //Problem is here, not gets called
        public string ResultText
        {
            get { return AT.ResultText; }
            set
            {
                if (AT.ResultText != value)
                {
                    AT.ResultText = value;
                    RaisePropertyChanged("ResultText");
                }
            }
        }

        public string CommandHelp
        {
            get { return AT.CommandHelp; }
            set
            {
                if (AT.CommandHelp != value)
                {
                    AT.CommandHelp = value;
                    RaisePropertyChanged("CommandHelp");
                }
            }
        }

        public string FlashFile
        {
            get { return Flash.FlashFile; }
            set
            {
                if (Flash.FlashFile != value)
                {
                    Flash.FlashFile = value;
                    RaisePropertyChanged("FlashFile");
                }
            }
        }

        public string UpgradeFileDownload
        {
            get { return Upgrade.UpgradeFileDownload; }
            set
            {
                if (Upgrade.UpgradeFileDownload != value)
                {
                    Upgrade.UpgradeFileDownload = value;
                    RaisePropertyChanged("UpgradeFileDownload");
                }
            }
        }


        #endregion

        #region ICommands

        //ICommand    
        void AwsFirmwareFileFlashExecute()
        {
            _flash.FlashOnDevice("DeviceX");
        }

        bool CanAwsFirmwareFileFlashExecute()
        {
            return true;
        }

        void FileBrowseExecute()
        {
            var dlg = new Microsoft.Win32.OpenFileDialog
            {
                Filter = "Firmware(FW) Files|*.fw|All Files(*.*)|*.*"
            };
            if (dlg.ShowDialog() == true)
            {
                FlashFile = dlg.FileName;
            }
        }

        bool CanFileBrowseExecute()
        {
            return true;
        }

        void AwsFirmwareFileDownloadExecute()
        {
            //TODO:
            //get aws file input by user
            _upgrade.DeviceFWUpgrade(FlashFile);
        }

        bool CanAwsFirmwareFileDownloadExecute()
        {
            return true;
        }

        void UpdateResultExecute()
        {
            _at.StatusText = "Run";
            _at.RunCmd(true);
            RaisePropertyChanged("ResultText");
            _at.StatusText = "done";
        }

        bool CanUpdateResultExecute()
        {
            return true;
        }

        public ICommand UpdateResult { get { return new RelayCommand(UpdateResultExecute, CanUpdateResultExecute); } }
        public ICommand FileBrowse { get { return new RelayCommand(FileBrowseExecute, CanFileBrowseExecute); } }
        public ICommand AwsFirmwareFileDownload { get { return new RelayCommand(AwsFirmwareFileDownloadExecute, CanAwsFirmwareFileDownloadExecute); } }
        public ICommand AwsFirmwareFileFlash { get { return new RelayCommand(AwsFirmwareFileFlashExecute, CanAwsFirmwareFileFlashExecute); } }

        #endregion

    }
}
