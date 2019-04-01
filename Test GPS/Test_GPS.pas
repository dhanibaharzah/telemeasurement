unit Test_GPS;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, CPort;

type
  TForm1 = class(TForm)
    Timer1: TTimer;
    Button1: TButton;
    Button2: TButton;
    Edit1: TEdit;
    Button3: TButton;
    Button4: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
begin
timer1.Enabled:=true;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
timer1.Enabled:=false;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
var   Count                           : integer;
      Alamat                          : char;
      RX_Data_ADC_Suhu, String_Suhu   : string;
begin
Comport1.Open;
sleep(100);
Alamat:='1';            //Aktifkan GPS
comport1.Write(alamat,1);
sleep(5000);        // Tungu refresh GPS


Alamat:='2';          // Minta Latide
Comport1.write(Alamat,1);
sleep(100);
Comport1.ReadStr(RX_Data_ADC_Suhu,Count);

  if RX_Data_ADC_Suhu[Count]=#13 then
    begin
      String_Suhu:=RX_Data_ADC_Suhu;
    end
  else
    begin
      String_Suhu:=RX_Data_ADC_Suhu;
    end;


edit1.Text:=String_Suhu;
Comport1.Close;
timer1.Enabled:=false;


end;

procedure TForm1.Button3Click(Sender: TObject);
begin
application.Terminate;
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
Comport1.ShowSetupDialog()
end;

end.
