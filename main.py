import typer, os
from pathlib import Path

app = typer.Typer()

@app.command()
def run(input_file: str, animal: str):
    dir_path = Path(os.path.realpath(__file__)).parent.absolute();
    src_path = os.path.join(dir_path, "src")
    os.chdir(src_path)
    os.system("make")
    os.system("./main " + input_file)
    print()
    print("---------------------------Dialog starts here-----------------------------")
    os.system("../out/" + animal)

if __name__ == "__main__":
    app()