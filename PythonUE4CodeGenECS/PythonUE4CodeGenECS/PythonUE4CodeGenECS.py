import sys
import string
import re
from tkinter import *
from tkinter import messagebox
from tkinter import filedialog
from TigerCodeGenDecoder import TigerCodeGenDecoder

def gui():
    def OnChooseSchemaClicked():
        filename = filedialog.askopenfilename(filetypes = (("Schema Files", "*.sch"), ("all files","*.*")))
        entry.delete(0, END)
        entry.insert(0, filename)

        global CodeGenDecoder
        CodeGenDecoder = TigerCodeGenDecoder()

        # read data from files
        with open(filename, "r") as schemaObj:
            data = schemaObj.read().replace('\n', '')
        schemaObj.close()

        # getting result and result2 using global variables.
        global result
        global result2
        
        result, result2 = CodeGenDecoder.TranslateSchemaIntoCode(data)


    def OnChooseFolderLocation():
        global folder_path
       
        folder_path = filedialog.askdirectory()
        folderpath.delete(0, END)
        folderpath.insert(0, folder_path)

    def OnGenerateCode():
        print(result)
        print(result2)
        
        codes, f_paths = CodeGenDecoder.GenerateCPlusPlusCode(result, result2, str(folder_path))

        # this will generate multiple C++ files.
        if(len(codes) == len(f_paths)):
            i = 0
            while (i < len(codes)):
                with open(f_paths[i], 'w') as FOUT:
                    FOUT.write(codes[i])

                FOUT.close()
                i+=1


    root = Tk()
    root.title("UE4 ECS SchemaGen")
    root.geometry('600x480')

    frame = Frame(root)
    frame.pack()

    ########################################## Choose Schema File ######################################
    
    lbl = Label(root, text="Choose Schema to Open", font=("Arial Bold", 20))
    lbl.pack()

    entry = Entry(root, width = 50)
    entry.pack()

    button_browse = Button(root, text="Browse Schema Location", command=OnChooseSchemaClicked)
    button_browse.pack()

    ########################################## Choose Code Gen Folder Location #################################

    lbl2 = Label(root, text="Choose Location to Generate Code", font=("Arial Bold", 18))
    lbl2.pack()
    
    folderpath = Entry(root, width = 50)
    folderpath.pack()

    btn_chooseFolder = Button(root, text="Choose Location", command = OnChooseFolderLocation)
    btn_chooseFolder.pack()
       
    ######################################### Code Gen Btn #########################################

    lbl3 = Label(root, text="Click Btn Below to Generate Code", font=("Arial Bold", 18))
    lbl3.pack()

    btn_codeGen = Button(root, text="Code Gen", command = OnGenerateCode)
    btn_codeGen.pack()

  
    root.mainloop()


if __name__ == '__main__':
    gui()
