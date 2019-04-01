unit CMB_VerB;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Grids, StdCtrls, CPort, ExtCtrls,DateUtils, DB, ADODB;

type
  TForm1 = class(TForm)
    ComPort1: TComPort;
    Button1: TButton;
    StringGrid1: TStringGrid;
    Label1: TLabel;
    Button2: TButton;
    Edit1: TEdit;
    Timer1: TTimer;
    Timer2: TTimer;
    Timer3: TTimer;
    Timer4: TTimer;
    Timer5: TTimer;
    Timer6: TTimer;
    Timer7: TTimer;
    Timer8: TTimer;
    Timer9: TTimer;
    Timer10: TTimer;
    Panel1: TPanel;
    Panel2: TPanel;
    Panel3: TPanel;
    Button3: TButton;
    Timer11: TTimer;
    ADOConnection1: TADOConnection;
    ADOTable1: TADOTable;
    Panel4: TPanel;
    Label2: TLabel;
    Edit2: TEdit;
    Label3: TLabel;
    Label4: TLabel;
    Edit3: TEdit;
    Label5: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure Timer2Timer(Sender: TObject);
    procedure Timer3Timer(Sender: TObject);
    procedure Timer4Timer(Sender: TObject);
    procedure Timer5Timer(Sender: TObject);
    procedure Timer6Timer(Sender: TObject);
    procedure Timer7Timer(Sender: TObject);
    procedure Timer8Timer(Sender: TObject);
    procedure Timer9Timer(Sender: TObject);
    procedure Timer10Timer(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Timer11Timer(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure StringGrid1DrawCell(Sender: TObject; ACol, ARow: Integer;
    Rect: TRect; State: TGridDrawState);

  private
    { Private declarations }
  public
    { Public declarations }

  end;

var
  Form1: TForm1;
  Waktu : TDateTime;
  Y,Mo,D,H,Mi,S,MS: Word;
  Hasil_ADC_T,Hasil_ADC_P, Hasil_ADC_V, Hasil_ADC_CO2,Hasil_ADC_N2, Hasil_ADC_CH4, Hasil_ADC_PM10 : integer;
  Hasil_T,Hasil_P,Hasil_V,Hasil_CO2,Hasil_N2,Hasil_CH4,Hasil_PM10:real;


implementation

{$R *.dfm}

//========================================================= Prosedur Form Create
procedure TForm1.FormCreate(Sender: TObject);
begin
stringgrid1.Cells[0,0]:=' STASION ';
stringgrid1.Cells[1,0]:='       WAKTU';
stringgrid1.Cells[2,0]:='     T (C)';
stringgrid1.Cells[3,0]:='     P (PSi)  ';
stringgrid1.Cells[4,0]:='  V (m/s)';
stringgrid1.Cells[5,0]:='  CO2 (ppm)';
stringgrid1.Cells[6,0]:='  N2 ppm)';
stringgrid1.Cells[7,0]:='  CH4 (ppm)';
stringgrid1.Cells[8,0]:=' PM10 (ppm)';
// Comport1.Open;
end;


procedure TForm1.Button2Click(Sender: TObject);
begin
Comport1.ShowSetupDialog;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
timer1.Enabled:=true;
timer2.Enabled:=false;
timer3.Enabled:=false;
timer4.Enabled:=false;
timer5.Enabled:=false;
timer6.Enabled:=false;
timer7.Enabled:=false;
timer8.Enabled:=false;
timer9.Enabled:=false;
timer10.Enabled:=false;
end;


//========================================================== Timer 1 : Time, N
Procedure TForm1.Timer1Timer(Sender: TObject);
Var     N     : integer;

begin
N:=strtoint(edit1.Text);
INC (N);
Edit1.Text:=inttostr(N);
Stringgrid1.Cells[0,N]:=panel4.Caption;
DecodeDateTime(Now,Y,Mo,D,H,Mi,S,MS);
Waktu:=EncodeDateTime(Y,Mo,D,H,Mi,S,MS);
Stringgrid1.Cells[1,N]:=DateTimetostr(Waktu);

Timer1.Enabled:=false;
Timer2.Enabled:=true;
Timer3.Enabled:=false;
Timer4.Enabled:=false;
Timer5.Enabled:=false;
Timer6.Enabled:=false;
Timer7.Enabled:=false;
Timer8.Enabled:=false;
Timer9.Enabled:=false;
timer10.Enabled:=false;
end;


//================================================= Timer 2 : T(Suhu, Alamat =1)
Procedure TForm1.Timer2Timer(Sender: TObject);
Var   N, Count                        : integer;
      Alamat                          : char;
      RX_Data_ADC_Suhu, String_Suhu   : string;

Begin
Comport1.Open;
sleep(500);
Alamat:='1';                                     // Minta suhu
Comport1.Write(Alamat,1);
Sleep(500);                                      //  Buat Mikro


ComPort1.ReadStr(RX_Data_ADC_Suhu,Count);

  if RX_Data_ADC_Suhu[Count]=#13 then
    begin
      String_Suhu:=RX_Data_ADC_Suhu;
    end
  else
    begin
      String_Suhu:=RX_Data_ADC_Suhu;
    end;

N:=strtoint(edit1.Text);
sleep(500);

edit2.Text:=String_Suhu;
Comport1.Close;
sleep(100);


Hasil_ADC_T :=strtoint(edit2.text);

Hasil_T := ((Hasil_ADC_T)/39.032144);    // Persamaaan karakterisasi
Edit3.Text:=Formatfloat('0.#0',Hasil_T);
Stringgrid1.Cells[2,N]:=Formatfloat('0.#0',Hasil_T);      // edit1.Text;
sleep(100);

timer1.Enabled:=false;
timer2.Enabled:=false;
timer3.Enabled:=true;
timer4.Enabled:=false;
timer5.Enabled:=false;
timer6.Enabled:=false;
timer7.Enabled:=false;
timer8.Enabled:=false;
timer9.Enabled:=false;
timer10.Enabled:=false;
end;


//========================================= Timer 3 : P (Tekanan, Alamat =2)
Procedure TForm1.Timer3Timer(Sender: TObject);
Var   N,Count                               : integer;
      Alamat                                : char;
      RX_Data_ADC_Tekanan, String_Tekanan   : string;

Begin
Comport1.Open;
Alamat:='2';                                     // Minta suhu
String_Tekanan :='2';
Comport1.Write(Alamat,1);
Sleep(500);                                      //  Buat Mikro


ComPort1.ReadStr(RX_Data_ADC_Tekanan, Count);

  if RX_Data_ADC_Tekanan[Count]=#13 then
    begin
      String_Tekanan:=RX_Data_ADC_Tekanan;
    end
  else
    begin
      String_Tekanan:=RX_Data_ADC_Tekanan;
    end;

N:=strtoint(edit1.Text);
sleep(500);

edit2.Text:=String_Tekanan;
Comport1.Close;
sleep(100);

Hasil_ADC_P :=strtoint(edit2.text);
Hasil_P := (0.08*Hasil_ADC_P)+1.597 ;                // Persamaaan karakterisasi
Edit3.Text:=Formatfloat('0.#0',Hasil_P);
  
Edit3.Text:=Formatfloat('0.#0',Hasil_P);
Stringgrid1.Cells[3,N]:=Formatfloat('0.#0',hasil_P);
sleep(100);

timer1.Enabled:=false;
timer2.Enabled:=false;
timer3.Enabled:=false;
timer4.Enabled:=true;
timer5.Enabled:=false;
timer6.Enabled:=false;
timer7.Enabled:=false;
timer8.Enabled:=false;
timer9.Enabled:=false;
timer10.Enabled:=false;
end;


//===================================================== Timer 4 : V Alamat = 3
Procedure TForm1.Timer4Timer(Sender: TObject);
Var   N,Count                               : integer;
      Alamat                                : char;
      RX_Data_ADC_Aliran, String_Aliran     : string;

Begin
Comport1.Open;
Alamat:='2';                                     // Minta suhu
String_Aliran :='2';
Comport1.Write(Alamat,1);
Sleep(500);                                      //  Buat Mikro


ComPort1.ReadStr(RX_Data_ADC_Aliran, Count);

  if RX_Data_ADC_Aliran[Count]=#13 then
    begin
      String_Aliran:=RX_Data_ADC_Aliran;
    end
  else
    begin
      String_Aliran:=RX_Data_ADC_Aliran;
    end;

N:=strtoint(edit1.Text);
sleep(500);

edit2.Text:=String_Aliran;
Comport1.Close;
sleep(100);

Hasil_ADC_V :=strtoint(edit2.text);
Hasil_V := (0.08*Hasil_ADC_V)+1.597 ;                // Persamaaan karakterisasi
Edit3.Text:=Formatfloat('0.#0',Hasil_V);

Edit3.Text:=Formatfloat('0.#0',Hasil_V);
Stringgrid1.Cells[4,N]:=Formatfloat('0.#0',hasil_V);
N:=strtoint(edit1.Text);
sleep(100);


timer1.Enabled:=false;
timer2.Enabled:=false;
timer3.Enabled:=false;
timer4.Enabled:=false;
timer5.Enabled:=true;
timer6.Enabled:=false;
timer7.Enabled:=false;
timer8.Enabled:=false;
timer9.Enabled:=false;
timer10.Enabled:=false;
end;


//====================================================== Timer 5 : CO2 ALamat : 4
Procedure TForm1.Timer5Timer(Sender: TObject);
Var   N,Count                               : integer;
      Alamat                                : char;
      RX_Data_ADC_C02, String_C02           : string;

Begin
Comport1.Open;
Alamat:='2';                                     // Minta suhu
String_C02 :='2';
Comport1.Write(Alamat,1);
Sleep(500);                                      //  Buat Mikro


ComPort1.ReadStr(RX_Data_ADC_C02, Count);

  if RX_Data_ADC_C02[Count]=#13 then
    begin
      String_C02:=RX_Data_ADC_C02;
    end
  else
    begin
      String_C02:=RX_Data_ADC_C02;
    end;

N:=strtoint(edit1.Text);
sleep(500);

edit2.Text:=String_C02;
Comport1.Close;
sleep(100);

Hasil_ADC_CO2:=strtoint(String_C02);
Hasil_CO2 := (0.08*Hasil_ADC_CO2)+1.597;
Edit3.Text:=Formatfloat('0.#0',Hasil_CO2);

Stringgrid1.Cells[5,N]:=Formatfloat('0.#0',hasil_CO2);

timer1.Enabled:=false;
timer2.Enabled:=false;
timer3.Enabled:=false;
timer4.Enabled:=false;
timer5.Enabled:=false;
timer6.Enabled:=true;
timer7.Enabled:=false;
timer8.Enabled:=false;
timer9.Enabled:=false;
timer10.Enabled:=false;
end;


//==================================================  Timer 6 : N2  Alamat ; 5
Procedure TForm1.Timer6Timer(Sender: TObject);
Var   N,Count                               : integer;
      Alamat                                : char;
      RX_Data_ADC_N2, String_N2             : string;

Begin
Comport1.Open;
Alamat:='2';                                     // Minta suhu
String_N2 :='2';
Comport1.Write(Alamat,1);
Sleep(500);                                      //  Buat Mikro


ComPort1.ReadStr(RX_Data_ADC_N2, Count);
  if RX_Data_ADC_N2[Count]=#13 then
    begin
      String_N2:=RX_Data_ADC_N2;
    end
  else
    begin
      String_N2:=RX_Data_ADC_N2;
    end;

N:=strtoint(edit1.Text);
sleep(500);

edit2.Text:=String_N2;
Comport1.Close;
sleep(100);

Hasil_ADC_N2:=strtoint(String_N2);
Hasil_N2 := (0.08*Hasil_ADC_N2)+1.597;
Edit3.Text:=Formatfloat('0.#0',Hasil_N2);
Stringgrid1.Cells[6,N]:=Formatfloat('0.#0',hasil_N2);
sleep(100);

timer1.Enabled:=false;
timer2.Enabled:=false;
timer3.Enabled:=false;
timer4.Enabled:=false;
timer5.Enabled:=false;
timer6.Enabled:=false;
timer7.Enabled:=true;
timer8.Enabled:=false;
timer9.Enabled:=false;
timer10.Enabled:=false;
end;



//==================================================  Timer 7 : CH4   Alamat : 6
Procedure TForm1.Timer7Timer(Sender: TObject);
Var   N,Count                               : integer;
      Alamat                                : char;
      RX_Data_ADC_CH4, String_CH4           : string;

Begin
Comport1.Open;
Alamat:='2';                                     // Minta suhu
String_CH4 :='2';
Comport1.Write(Alamat,1);
Sleep(500);                                      //  Buat Mikro


ComPort1.ReadStr(RX_Data_ADC_CH4, Count);
  if RX_Data_ADC_CH4[Count]=#13 then
    begin
      String_CH4:=RX_Data_ADC_CH4;
    end
  else
    begin
      String_CH4:=RX_Data_ADC_CH4;
    end;

N:=strtoint(edit1.Text);
sleep(500);

edit2.Text:=String_CH4;
Comport1.Close;
sleep(100);

Hasil_ADC_CH4:=strtoint(String_CH4);
Hasil_CH4 := (0.08*Hasil_ADC_CH4)+1.597;
Edit3.Text:=Formatfloat('0.#0',Hasil_CH4);
Stringgrid1.Cells[7,N]:=Formatfloat('0.#0',hasil_CH4);
sleep(100);

timer1.Enabled:=false;
timer2.Enabled:=false;
timer3.Enabled:=false;
timer4.Enabled:=false;
timer5.Enabled:=false;
timer6.Enabled:=false;
timer7.Enabled:=false;
timer8.Enabled:=true;
timer9.Enabled:=false;
timer10.Enabled:=false;
end;


//==================================================== Timer 8 : PM10 Alamat : 7
Procedure TForm1.Timer8Timer(Sender: TObject);
Var   N,Count                               : integer;
      Alamat                                : char;
      RX_Data_ADC_PM10, String_PM10         : string;

Begin
Comport1.Open;
Alamat:='2';                                     // Minta suhu
String_PM10 :='2';
Comport1.Write(Alamat,1);
Sleep(500);                                      //  Buat Mikro


ComPort1.ReadStr(RX_Data_ADC_PM10, Count);
  if RX_Data_ADC_PM10[Count]=#13 then
    begin
      String_PM10:=RX_Data_ADC_PM10;
    end
  else
    begin
      String_PM10:=RX_Data_ADC_PM10;
    end;

N:=strtoint(edit1.Text);
sleep(500);

edit2.Text:=String_PM10;
Comport1.Close;
sleep(100);

Hasil_ADC_PM10:=strtoint(String_PM10);
Hasil_PM10 := (0.08*Hasil_ADC_PM10)+1.597;
Edit3.Text:=Formatfloat('0.#0',Hasil_PM10);
Stringgrid1.Cells[8,N]:=Formatfloat('0.#0',hasil_PM10);
sleep(100);
timer1.Enabled:=false;
timer2.Enabled:=false;
timer3.Enabled:=false;
timer4.Enabled:=false;
timer5.Enabled:=false;
timer6.Enabled:=false;
timer7.Enabled:=false;
timer8.Enabled:=false;
timer9.Enabled:=false;        // Tidak merekam DB
timer10.Enabled:=true;
end;

//=========================================================  Timer 9 : Record DB
procedure TForm1.Timer9Timer(Sender: TObject);
begin
Adotable1.Open;
Adotable1.InsertRecord(['001',Waktu,hasil_T,hasil_P,hasil_V,hasil_CO2,hasil_N2,hasil_CH4,hasil_PM10]);
Adotable1.Close;

timer1.Enabled:=false;
timer2.Enabled:=false;
timer3.Enabled:=false;
timer4.Enabled:=false;
timer5.Enabled:=false;
timer6.Enabled:=false;
timer7.Enabled:=false;
timer8.Enabled:=false;
timer9.Enabled:=false;
timer10.Enabled:=true;

end;



//============================================================== Timer 10: Reset
Procedure TForm1.Timer10Timer(Sender: TObject);
Var  N, K :integer;
begin
 N:= strtoint(edit1.Text);

 if N=10  then

begin
  edit1.Text:='0';

For K:=0 to 10 do

Begin
stringgrid1.Cells[K,1]:=' ';
end;

For K:=0 to 10 do
Begin
stringgrid1.Cells[K,2]:=' ';
end;
For K:=0 to 10 do
Begin
stringgrid1.Cells[K,3]:=' ';
end;
For K:=0 to 10 do
Begin
stringgrid1.Cells[K,4]:=' ';
end;
For K:=0 to 10 do
Begin
stringgrid1.Cells[K,5]:=' ';
end;

For K:=0 to 10 do
Begin
stringgrid1.Cells[K,6]:=' ';
end;
For K:=0 to 10 do
Begin
stringgrid1.Cells[K,7]:=' ';
end;
For K:=0 to 10 do
Begin
stringgrid1.Cells[K,8]:=' ';
end;
For K:=0 to 10 do
Begin
stringgrid1.Cells[K,9]:=' ';
end;
For K:=0 to 10 do
Begin
stringgrid1.Cells[K,10]:=' ';
timer1.Enabled:=true;
end;
end

Else

Begin
timer1.Enabled:=true;
end

end;


//============================================================ Timer 11 : Waktu
procedure TForm1.Timer11Timer(Sender: TObject);
VAR

hour, min, sec, msec: word;

Begin
Panel1.Caption := FormatDateTime('DDDD',Date);
Panel2.Caption := FormatDateTime('DD MMMM YYYY',Date);
Panel3.Caption := FormatDateTime('HH : MM : SS am/pm',Time);
DecodeTime(time, hour, min, sec, msec );

End;


//============================================================ Buuton 3 : Exit
 procedure TForm1.Button3Click(Sender: TObject);
begin
Application.Terminate;
end;


procedure TForm1.Button4Click(Sender: TObject);
Var   Hasilnya: byte;
      Alamat: integer;
begin
comport1.Open;
alamat:=1;
comport1.Write(alamat,1);
sleep(200);
comport1.Read(hasilnya,1);
edit2.Text:=floattostr(hasilnya);
end;

procedure TForm1.StringGrid1DrawCell(Sender: TObject; ACol, ARow: Integer;
  Rect: TRect; State: TGridDrawState);
 Var  S           : string;
      SavedAlign  : word;

  begin
    if ACol = 0 Then
    Begin
    S:=Stringgrid1.Cells[Acol,Arow];
    SavedAlign :=SetTextAlign(StringGrid1.Canvas.Handle, TA_Center);
    Stringgrid1.Canvas.TextRect(Rect, Rect.Left + (Rect.Right - Rect.Left)DIV 2,
    Rect.top+2,S);
    SetTextAlign(Stringgrid1.Canvas.Handle, SavedAlign);
    End;

    if ACol = 1 Then
    Begin
    S:=Stringgrid1.Cells[Acol,Arow];
    SavedAlign :=SetTextAlign(StringGrid1.Canvas.Handle, TA_Center);
    Stringgrid1.Canvas.TextRect(Rect, Rect.Left + (Rect.Right - Rect.Left)DIV 2,
    Rect.top+2,S);
    SetTextAlign(Stringgrid1.Canvas.Handle, SavedAlign);
    End;

    if ACol = 2 Then
    Begin
    S:=Stringgrid1.Cells[Acol,Arow];
    SavedAlign :=SetTextAlign(StringGrid1.Canvas.Handle, TA_Center);
    Stringgrid1.Canvas.TextRect(Rect, Rect.Left + (Rect.Right - Rect.Left)DIV 2,
    Rect.top+2,S);
    SetTextAlign(Stringgrid1.Canvas.Handle, SavedAlign);
    End;

    if ACol = 3 Then
    Begin
    S:=Stringgrid1.Cells[Acol,Arow];
    SavedAlign :=SetTextAlign(StringGrid1.Canvas.Handle, TA_Center);
    Stringgrid1.Canvas.TextRect(Rect, Rect.Left + (Rect.Right - Rect.Left)DIV 2,
    Rect.top+2,S);
    SetTextAlign(Stringgrid1.Canvas.Handle, SavedAlign);
    End;

    if ACol = 4 Then
    Begin
    S:=Stringgrid1.Cells[Acol,Arow];
    SavedAlign :=SetTextAlign(StringGrid1.Canvas.Handle, TA_Center);
    Stringgrid1.Canvas.TextRect(Rect, Rect.Left + (Rect.Right - Rect.Left)DIV 2,
    Rect.top+2,S);
    SetTextAlign(Stringgrid1.Canvas.Handle, SavedAlign);
    End;

    if ACol = 5 Then
    Begin
    S:=Stringgrid1.Cells[Acol,Arow];
    SavedAlign :=SetTextAlign(StringGrid1.Canvas.Handle, TA_Center);
    Stringgrid1.Canvas.TextRect(Rect, Rect.Left + (Rect.Right - Rect.Left)DIV 2,
    Rect.top+2,S);
    SetTextAlign(Stringgrid1.Canvas.Handle, SavedAlign);
    End;


    if ACol = 6 Then
    Begin
    S:=Stringgrid1.Cells[Acol,Arow];
    SavedAlign :=SetTextAlign(StringGrid1.Canvas.Handle, TA_Center);
    Stringgrid1.Canvas.TextRect(Rect, Rect.Left + (Rect.Right - Rect.Left)DIV 2,
    Rect.top+2,S);
    SetTextAlign(Stringgrid1.Canvas.Handle, SavedAlign);
    End;

    if ACol = 7 Then
    Begin
    S:=Stringgrid1.Cells[Acol,Arow];
    SavedAlign :=SetTextAlign(StringGrid1.Canvas.Handle, TA_Center);
    Stringgrid1.Canvas.TextRect(Rect, Rect.Left + (Rect.Right - Rect.Left)DIV 2,
    Rect.top+2,S);
    SetTextAlign(Stringgrid1.Canvas.Handle, SavedAlign);
    End;

    if ACol = 8 Then
    Begin
    S:=Stringgrid1.Cells[Acol,Arow];
    SavedAlign :=SetTextAlign(StringGrid1.Canvas.Handle, TA_Center);
    Stringgrid1.Canvas.TextRect(Rect, Rect.Left + (Rect.Right - Rect.Left)DIV 2,
    Rect.top+2,S);
    SetTextAlign(Stringgrid1.Canvas.Handle, SavedAlign);
    End;

end;

   
end.