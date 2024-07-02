import { useNavigate } from 'react-router-dom';
import { Layout } from '../../shared/components/layout/Layout';

import './ProfilePage.css';
import { useEffect, useRef, useState } from 'react';
import { User } from '../../models/user';
import { getUserById, updateUser } from '../../services/Users Service/UsersService';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faPlus } from '@fortawesome/free-solid-svg-icons';
import { FormEntry } from '../../features/CRUD Operations/User Form/Form Entry/FormEntry';
import { Button } from '../../shared/components/button/Button';
import { saveImage } from '../../services/Images Service/ImagesService';
import LoadingPage from '../Loading Page/LoadingPage';
import DealerMap from '../../features/Map/DealerMap';
import { getDealerLocation, updateDealerLocation } from '../../services/Location Service/LocationService';
import ReactLoading from 'react-loading';

function getUserDataFromInputs(
    firstNameInput: React.RefObject<HTMLInputElement>,
    lastNameInput: React.RefObject<HTMLInputElement>,
    emailInput: React.RefObject<HTMLInputElement>,
) {
    if (!firstNameInput.current?.value || !lastNameInput.current?.value || !emailInput.current?.value)
        throw new Error('You must provide value for each field!');

    const firstName = firstNameInput.current.value;
    const lastName = lastNameInput.current.value;
    const email = emailInput.current.value;

    return {
        firstName,
        lastName,
        email,
    };
}

export default function ProfilePage() {
    const navigate = useNavigate();
    const [user, setUser] = useState<User>();
    const [isLoading, setIsLoading] = useState<boolean>(true);
    const [profileImage, setProfileImage] = useState<File>();
    const [success, setSuccess] = useState<boolean>(false);

    const [latitude, setLatitude] = useState<number>();
    const [longitude, setLongitude] = useState<number>();

    const firstNameInput = useRef<HTMLInputElement>(null);
    const lastNameInput = useRef<HTMLInputElement>(null);
    const emailInput = useRef<HTMLInputElement>(null);

    const role = localStorage.getItem('userRole')!;

    const handleImageUpload = (event: any) => {
        if (!event.target.files[0]) return;
        setProfileImage(event.target.files[0]);
    };

    const handleUpdateClick = () => {
        const { firstName, lastName, email } = getUserDataFromInputs(firstNameInput, lastNameInput, emailInput);
        console.log(firstName, lastName, email);
        console.log(latitude, longitude);

        const userDTO = {
            id: user!.getId(),
            firstName: firstName,
            lastName: lastName,
            email: email,
            userRole: user!.getRole(),
        };

        setSuccess(true);

        updateUser(userDTO);
        if (profileImage !== undefined) saveImage(profileImage, user!.getId()).then(() => localStorage.removeItem('profileImage'));
        if (latitude && longitude) updateDealerLocation(user!.getId(), latitude, longitude);

        setTimeout(() => {
            navigate('/home');
        }, 3000);
    };

    useEffect(() => {
        if (!localStorage.getItem('userId')) navigate('/login');

        getUserById(localStorage.getItem('userId')!).then((response) => {
            setUser(response);
            setIsLoading(false);
        });

        getDealerLocation(parseInt(localStorage.getItem('userId')!)).then((response) => {
            setLatitude(response.data.latitude);
            setLongitude(response.data.longitude);
        });
    }, []);

    if (isLoading) return <LoadingPage />;

    return (
        <Layout>
            <div className='main-content-profile'>
                <label htmlFor='profile-image' className='profile-image-label'>
                    <img src={profileImage ? URL.createObjectURL(profileImage) : 'assets/default-user.png'} className='add-image' />
                    <FontAwesomeIcon icon={faPlus} className='add-button' />
                </label>
                <input type='file' id='profile-image' accept='.jpg,.jpeg,.png' onChange={handleImageUpload} />
                <div className='profile-details'>
                    <FormEntry label='First name' defaultValue={user?.getFirstName()} ref={firstNameInput} />
                    <FormEntry label='Last name' defaultValue={user?.getLastName()} ref={lastNameInput} />
                    <FormEntry label='Email' defaultValue={user?.getEmail()} ref={emailInput} />
                    <FormEntry label='Role' defaultValue={user?.getRole()} disabled={true} />
                </div>

                {role === 'MANAGER' && (
                    <DealerMap latitude={latitude} longitude={longitude} setLatitude={setLatitude} setLongitude={setLongitude} />
                )}

                <Button type='button' buttonMessage='Update' onClick={handleUpdateClick} />

                {success && <ReactLoading type='spin' width={30} height={30} color='black' />}
            </div>
        </Layout>
    );
}
