import { getImageByUserId } from '../../services/Images Service/ImagesService';
import { UserCardPropsType } from '../../types/UserCardProps.types';

import './UserCard.css';
import { useEffect, useState } from 'react';

/**
 * UserCard Component
 *
 * A component representing a card view for displaying user details.
 *
 * This component renders a card displaying user information such as profile picture,
 * first name, last name, and age. It also provides buttons for editing user details,
 * viewing the user's cars, and removing the user (via modal confirmation).
 *
 * @component
 * @param {Object} props - The props object containing the givenUser data.
 * @param {User} props.givenUser - The user object containing details to be displayed.
 * @returns {JSX.Element} - Rendered UserCard component.
 * @example
 * <UserCard givenUser={userData} />
 */
export function UserCard({ givenUser }: UserCardPropsType) {
    const [path, setPath] = useState<string>('/assets/default-user.png');

    // const handleViewCarsClick = (event: any) => {
    //     event.stopPropagation();
    //     event.preventDefault();
    //     console.log('View cars button clicked');
    //     navigate('/cars/' + givenUser.getId());
    // };

    // const modalContext = useContext(ModalContext)!;
    // const setUserId = modalContext.setUserId;
    // const setModalStatus = modalContext.setModalStatus;

    useEffect(() => {
        getImageByUserId(givenUser.id!).then((response) => {
            setPath('data:image/jpg;base64,' + response);
        });
    }, []);

    return (
        <div className='card' data-testid='user-card'>
            {/* <button
                className='remove-button'
                data-testid='remove-button'
                onClick={(e) => {
                    e.stopPropagation();
                }}
            >
                X
            </button> */}

            <div className='card-info'>
                <div className='picture'>
                    <img src={path} alt='user profile' />
                </div>

                <div className='user-info'>
                    <div className='first-name'>{givenUser.firstName}</div>
                    <div className='last-name'>{givenUser.lastName}</div>
                    <div className='email'>{givenUser.email}</div>
                    <div className='role'>{givenUser.userRole}</div>
                </div>
            </div>

            {/* <Button type='button' buttonMessage='View cars' onClick={handleViewCarsClick} /> */}
        </div>
    );
}
