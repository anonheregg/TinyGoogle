import os
import shutil
import subprocess
i=0
while(0<1):
    folder_c=os.listdir("images")
    for items in folder_c:
        if(str(items)[-4:]=="jpeg"):
            with open("image_list.txt",'a') as file:
                file.write(f"moved_images/{items}\n")
                source_path = f"images/{items}"
                destination_path = f"moved_images/{items}"
                os.rename(source_path, destination_path)
                i+=1
                if(i==4):
                    command=['python3','detect.py','--weights','yolov5s.pt','--source','image_list.txt']
                    process=subprocess.Popen(command,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
                    stdout,stderr=process.communicate()
                    return_code=process.returncode
                    print('error:',stderr.decode('utf'))
                    file.truncate(0)
                    i=0
                    break
        

        

