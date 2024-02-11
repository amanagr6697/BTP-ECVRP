import pandas as pd
import requests
import os

# Read Excel file with roll numbers and Google Drive links
df = pd.read_excel(r'C:\Users\agraw\OneDrive\Documents\Resume.xlsx')

# Create a folder to save downloaded files
download_folder = 'downloaded_resumes'
os.makedirs(download_folder, exist_ok=True)

# Loop through rows
for index, row in df.iterrows():
    roll_number = str(row['RollNumber'])
    drive_link = row['Resume']

    # Get file content using requests
    response = requests.get(drive_link)
    
    # Download file using requests
    output_path = os.path.join(download_folder, f'{roll_number}.pdf')
    with open(output_path, 'wb') as f:
        f.write(response.content)

print("Download complete.")
