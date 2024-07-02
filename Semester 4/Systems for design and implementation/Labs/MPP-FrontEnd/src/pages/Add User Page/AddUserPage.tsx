// import { UserForm } from '../../features/CRUD Operations/User Form/UserForm';
// import { Layout } from '../../shared/components/layout/Layout';
// import { Button } from '../../shared/components/button/Button';

// import { useContext, useRef, useState } from 'react';
// import { useNavigate } from 'react-router-dom';

// import './AddUserPage.css';
// import { UserDTO } from '../../types/UserDTO.types';
// import { addUser } from '../../services/Users Service/UsersService';
// import { ConnectionStatusContext } from '../../contexts/ConnectionStatusContext';
// import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
// import { faPlus } from '@fortawesome/free-solid-svg-icons';

// function handleOnClick(
//     firstNameInput: React.RefObject<HTMLInputElement>,
//     lastNameInput: React.RefObject<HTMLInputElement>,
//     urlInput: React.RefObject<HTMLInputElement>,
//     ageInput: React.RefObject<HTMLInputElement>,
// ): UserDTO {
//     // if (!imageInput.current!.files || !imageInput.current!.files[0]) throw new Error('You must provide a profile image!');

//     if (!firstNameInput.current!.value || !lastNameInput.current!.value || !urlInput.current!.value || !ageInput.current!.value)
//         throw new Error('You must provide values for each field!');

//     const firstName: string = firstNameInput.current!.value,
//         lastName: string = lastNameInput.current!.value,
//         pictureUrl: string = urlInput.current!.value,
//         age: number = parseInt(ageInput.current!.value);

//     return {
//         firstName,
//         lastName,
//         pictureUrl,
//         age,
//     };
// }

// export default function AddUserPage() {
//     document.title = 'Add user';

//     const [profileImage, setProfileImage] = useState<File>();

//     const firstNameInput = useRef<HTMLInputElement>(null);
//     const lastNameInput = useRef<HTMLInputElement>(null);
//     const urlInput = useRef<HTMLInputElement>(null);
//     const ageInput = useRef<HTMLInputElement>(null);
//     const imageInput = useRef<HTMLInputElement>(null);

//     const connectionContext = useContext(ConnectionStatusContext)!;

//     const navigate = useNavigate();
//     const isOnline = connectionContext.isOnline;
//     const isServerOnline = connectionContext.isServerOnline;

//     const handleImageUpload = (event: any) => {
//         if (!event.target.files[0]) return;
//         setProfileImage(event.target.files[0]);
//         console.log(event.target.files[0]);
//     };

//     const handleOnClickWrapper = () => {
//         try {
//             const inputUser = handleOnClick(firstNameInput, lastNameInput, urlInput, ageInput);
//             const users: UserDTO[] = JSON.parse(localStorage.getItem('users')!);

//             if (!isOnline || !isServerOnline) {
//                 users.push(inputUser);
//                 localStorage.setItem('users', JSON.stringify(users));
//                 navigate('/');
//             } else {
//                 // saveImage(profileImage!);
//                 addUser(inputUser, profileImage).then(() => navigate('/'));
//             }

//             navigate('/');
//         } catch (error) {
//             alert(error);
//         }
//     };

//     return (
//         <Layout>
//             <div className='main-page-container' data-testid='main-page-container'>
//                 <label htmlFor='profile-image' className='profile-image-label'>
//                     <img src={profileImage ? URL.createObjectURL(profileImage) : 'assets/default-user.png'} className='add-image' />
//                     <FontAwesomeIcon icon={faPlus} className='add-button' />
//                 </label>
//                 <input type='file' id='profile-image' accept='.jpg,.jpeg,.png' onChange={handleImageUpload} ref={imageInput} />

//                 <UserForm
//                     firstNameInput={firstNameInput}
//                     lastNameInput={lastNameInput}
//                     urlInput={urlInput}
//                     ageInput={ageInput}
//                     data-testid='user-form'
//                 />

//                 <Button type='submit' buttonMessage='Add user' className='form-button' onClick={handleOnClickWrapper} />
//             </div>
//         </Layout>
//     );
// }
