import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { Layout } from '../../shared/components/layout/Layout';

import './AdminDashboardPage.css';
import { faCar, faChartSimple, faUserGroup, faUserPlus } from '@fortawesome/free-solid-svg-icons';
import { useContext, useState } from 'react';
import CarGallery from '../../features/Car Gallery/CarGallery';
import CarsChart from '../../features/Cars Chart/CarsChart';
import { RegistrationForm } from '../../features/Authentication/Register Form/RegistrationForm';
import { ConnectionStatusContext } from '../../contexts/ConnectionStatusContext';
import { addUser } from '../../services/Users Service/UsersService';
import { UserDTO } from '../../types/UserDTO.types';
import UsersGallery from '../../features/Users Gallery/UsersGallery';

export default function AdminDashboardPage() {
    const [selectedItem, setSelectedItem] = useState<string>('user');

    const connectionStatusContext = useContext(ConnectionStatusContext)!;

    const handleSelectionChange = (item: string) => {
        setSelectedItem(item);
    };

    const handleRegister = (firstName: string, lastName: string, email: string, password: string, userRole: string) => {
        const isOnline = connectionStatusContext.isOnline;
        const isServerOnline = connectionStatusContext.isServerOnline;

        const inputUser: UserDTO = { firstName, lastName, email, password, userRole };

        if (isOnline && isServerOnline) addUser(inputUser);
        else {
            const users: UserDTO[] = JSON.parse(localStorage.getItem('users')!);
            users.push(inputUser);

            localStorage.setItem('users', JSON.stringify(users));
        }
    };

    return (
        <Layout>
            <div className='admin-dashboard'>
                <div className='side-menu'>
                    <div
                        className={`option ${selectedItem === 'user' ? 'selected' : ''}`}
                        data-testid='user-view'
                        onClick={() => handleSelectionChange('user')}
                    >
                        <FontAwesomeIcon icon={faUserGroup} className={'option-icon'} />
                        <div className='option-users'>Users</div>
                    </div>

                    <div
                        className={`option ${selectedItem === 'car' ? 'selected' : ''}`}
                        data-testid='cars-view'
                        onClick={() => handleSelectionChange('car')}
                    >
                        <FontAwesomeIcon icon={faCar} className='option-icon' />
                        <div className='option-cars'>Cars</div>
                    </div>

                    <div
                        className={`option ${selectedItem === 'chart' ? 'selected' : ''}`}
                        data-testid='chart-view'
                        onClick={() => handleSelectionChange('chart')}
                    >
                        <FontAwesomeIcon icon={faChartSimple} className='option-icon' />
                        <div className='option-chart'>Chart</div>
                    </div>

                    <div
                        className={`option ${selectedItem === 'add-user' ? 'selected' : ''}`}
                        onClick={() => handleSelectionChange('add-user')}
                    >
                        <FontAwesomeIcon icon={faUserPlus} className='option-icon' />
                        <div className='option-chart'>Add user</div>
                    </div>
                </div>
                <div className='content'>
                    {selectedItem === 'user' && <UsersGallery />}
                    {selectedItem === 'car' && <CarGallery />}
                    {selectedItem === 'chart' && <CarsChart />}
                    {selectedItem === 'add-user' && <RegistrationForm handleRegister={handleRegister} />}
                </div>
            </div>
        </Layout>
    );
}
