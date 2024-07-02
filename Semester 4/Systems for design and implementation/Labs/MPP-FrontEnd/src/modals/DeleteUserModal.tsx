import { useContext } from 'react';
import { Button } from '../shared/components/button/Button';

import { ModalContext } from '../contexts/ModalContext';

import './DeleteUserModal.css';
import { deleteUser } from '../services/Users Service/UsersService';

export const DeleteUserModal = () => {
    const modalContext = useContext(ModalContext)!;
    const modalStatus = modalContext.modalStatus;
    const setModalStatus = modalContext.setModalStatus;
    const removeUser = modalContext.removeUser;
    const userId = modalContext.userId;

    const handleYesClick = () => {
        deleteUser(userId).then(() => {
            setModalStatus(false);
            removeUser(userId);
        });
    };

    return (
        modalStatus && (
            <div id='modal-overlay' data-testid='modal-overlay-test' onClick={() => setModalStatus(false)}>
                <div id='modal-card' data-testid='modal-card-test' onClick={(e) => e.stopPropagation()}>
                    <div id='modal-text'>Are you sure you want to remove this user?</div>

                    <div id='buttons-list'>
                        <Button
                            type='button'
                            data_test_id='yes-button'
                            buttonMessage='Yes'
                            backgroundColor='#4CAF50'
                            onClick={handleYesClick}
                        />
                        <Button
                            type='button'
                            data_test_id='no-button'
                            buttonMessage='No'
                            backgroundColor='#E53935'
                            onClick={() => setModalStatus(false)}
                        />
                    </div>
                </div>
            </div>
        )
    );
};
