object Form1: TForm1
  Left = 186
  Top = 48
  Width = 1010
  Height = 568
  Caption = 'Suryono@fisika.undip.ac.id'
  Color = clLime
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 184
    Top = 32
    Width = 618
    Height = 39
    Caption = 'COAL BED METHANE ACQUISITION SYSTEM'
    Color = clLime
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlue
    Font.Height = -29
    Font.Name = '@Arial Unicode MS'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object Label2: TLabel
    Left = 136
    Top = 466
    Width = 82
    Height = 22
    Caption = 'Stasion :'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 136
    Top = 99
    Width = 61
    Height = 20
    Caption = 'LINE :  '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 400
    Top = 96
    Width = 71
    Height = 20
    Caption = 'AQDAT :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label5: TLabel
    Left = 648
    Top = 96
    Width = 102
    Height = 20
    Caption = 'KONVERSI :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Button1: TButton
    Left = 16
    Top = 144
    Width = 97
    Height = 65
    Caption = 'MULAI'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnClick = Button1Click
  end
  object StringGrid1: TStringGrid
    Left = 136
    Top = 144
    Width = 761
    Height = 281
    Color = clInfoBk
    ColCount = 9
    FixedColor = clYellow
    RowCount = 11
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    OnDrawCell = StringGrid1DrawCell
    ColWidths = (
      64
      146
      74
      68
      71
      72
      74
      78
      83)
    RowHeights = (
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24)
  end
  object Button2: TButton
    Left = 16
    Top = 256
    Width = 97
    Height = 57
    Caption = 'COM'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = Button2Click
  end
  object Edit1: TEdit
    Left = 208
    Top = 88
    Width = 121
    Height = 32
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    Text = '0'
  end
  object Panel1: TPanel
    Left = 384
    Top = 456
    Width = 153
    Height = 41
    Caption = 'Panel1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
  end
  object Panel2: TPanel
    Left = 560
    Top = 456
    Width = 145
    Height = 41
    Caption = 'Panel2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
  end
  object Panel3: TPanel
    Left = 728
    Top = 456
    Width = 145
    Height = 41
    Caption = 'Panel3'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
  end
  object Button3: TButton
    Left = 16
    Top = 360
    Width = 97
    Height = 65
    Caption = 'KELUAR'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 7
    OnClick = Button3Click
  end
  object Panel4: TPanel
    Left = 224
    Top = 456
    Width = 105
    Height = 41
    Caption = '001'
    Color = clNavy
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clYellow
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 8
  end
  object Edit2: TEdit
    Left = 480
    Top = 88
    Width = 121
    Height = 32
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 9
  end
  object Edit3: TEdit
    Left = 760
    Top = 88
    Width = 121
    Height = 32
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 10
  end
  object ComPort1: TComPort
    BaudRate = br9600
    Port = 'COM9'
    Parity.Bits = prNone
    StopBits = sbOneStopBit
    DataBits = dbEight
    Events = [evRxChar, evTxEmpty, evRxFlag, evRing, evBreak, evCTS, evDSR, evError, evRLSD, evRx80Full]
    FlowControl.OutCTSFlow = False
    FlowControl.OutDSRFlow = False
    FlowControl.ControlDTR = dtrDisable
    FlowControl.ControlRTS = rtsDisable
    FlowControl.XonXoffOut = False
    FlowControl.XonXoffIn = False
    Left = 840
    Top = 48
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 152
    Top = 120
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = Timer2Timer
    Left = 368
    Top = 120
  end
  object Timer3: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = Timer3Timer
    Left = 456
    Top = 120
  end
  object Timer4: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = Timer4Timer
    Left = 520
    Top = 120
  end
  object Timer5: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = Timer5Timer
    Left = 592
    Top = 120
  end
  object Timer6: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = Timer6Timer
    Left = 672
    Top = 120
  end
  object Timer7: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = Timer7Timer
    Left = 744
    Top = 120
  end
  object Timer8: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = Timer8Timer
    Left = 824
    Top = 120
  end
  object Timer9: TTimer
    Enabled = False
    OnTimer = Timer9Timer
    Left = 16
    Top = 472
  end
  object Timer10: TTimer
    Enabled = False
    Interval = 3000
    OnTimer = Timer10Timer
    Left = 56
    Top = 472
  end
  object Timer11: TTimer
    OnTimer = Timer11Timer
    Left = 96
    Top = 472
  end
  object ADOConnection1: TADOConnection
    ConnectionString = 
      'Provider=MSDASQL.1;Persist Security Info=False;Data Source=senso' +
      'r'
    Provider = 'MSDASQL.1'
    Left = 16
    Top = 424
  end
  object ADOTable1: TADOTable
    ConnectionString = 
      'Provider=MSDASQL.1;Persist Security Info=False;Data Source=senso' +
      'r'
    CursorType = ctStatic
    TableName = 'sensor'
    Left = 72
    Top = 424
  end
end
