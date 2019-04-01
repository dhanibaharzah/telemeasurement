program CBM_Project_VerB;

uses
  Forms,
  CMB_VerB in 'CMB_VerB.pas' {Form1};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
