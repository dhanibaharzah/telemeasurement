program Test_GPS_Prj;

uses
  Forms,
  Test_GPS in 'Test_GPS.pas' {Form1};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
