import React, { useState, Dispatch, SetStateAction} from 'react';
import style from '../style.module.css';
import UsePopUp from './usePopUp';
import { useNavigate } from 'react-router-dom';
import PopUp from './popUp';
import EditIcon from '../../../assets/edit.png';

interface EditImageProps {
  imageUrl: string;
  setImageUrl: Dispatch<SetStateAction<string>>;
}

const EditImage: React.FC<EditImageProps> = ({ imageUrl, setImageUrl }) => {
  const { isOpen, toggle } = UsePopUp();
  const [file, setFile] = useState<any>(null);
  const [errorMessage, setErrorMessage] = useState<string>('');
  const navigate = useNavigate();

  const resetErrorMessage = () => {
    setErrorMessage('');
  };

  const getBase64 = (img: any, callback: (url: string) => void) => {
    const reader = new FileReader();
    reader.addEventListener('load', () => callback(reader.result as string));
    reader.readAsDataURL(img);
  };

  const handleSubmit = (event: any) => {

    event.preventDefault();


		const formData = new FormData()
		formData.append('file', file)

		if (file !== null) {
      fetch(`${process.env.REACT_APP_BE_URL}/users/set-avatar`, {
        method: 'POST',
        body: formData,
        credentials: "include"
      })
      .then(response => { 
        if (!response.ok) {
          window.location.href = '/';
        }
        getBase64(file, (url) => {
          setImageUrl(url);
        });
        toggle();
        navigate(0);
      })
      .catch(error => {
        console.error('Error uploading file: ', error);
      });

		}
		else {
		}
	}

  const handleFileChange = (event: any) => {

    event.preventDefault();


    const selectedFile = event.target.files[0];
    const maxSize = 1 * 1024 * 1024; // (1 МБ)
    if (
      selectedFile === null ||
      selectedFile === undefined ||
      !['image/jpeg', 'image/jpg', 'image/png'].includes(selectedFile.type)
    ) {
      setFile(null);
      setErrorMessage('Invalid file, supported file types: jpeg, jpg, png');
    } else if (selectedFile.size > maxSize) {
      setFile(null);
      setErrorMessage('File size exceeds the limit 1 Mb');
    } else {
      setFile(selectedFile);
      setErrorMessage('');
    }
	}

  return (
    <div className={style["photoChange"]}>

    <button onClick={toggle} > 
      <img src={EditIcon} alt='editIcon' />  
    </button>

    <PopUp isOpen={isOpen} toggle={toggle} resetErrorMessage={resetErrorMessage}>
      <form onSubmit={handleSubmit} className={style["photoChangeForm"]}>
        <h1>Change profile picture</h1>

        <label htmlFor="avatar-input">
        <input
          type="file"
          id="avatar-input"
          className={style["avatar-input"]}
          onChange={handleFileChange}
          /> 
          </label>
        {errorMessage && <p className={style["noFriends"]}>{errorMessage}</p>}
        <button type="submit" className={style["avatar-button"]} onClick={handleSubmit} >
          change
        </button>
      </form>
    </PopUp>
    </div>
  );
};
  
export default EditImage;
