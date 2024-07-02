import { Footer } from '../footer/Footer';
import { Header } from '../header/Header';
import './Layout.css';

type LayoutProps = {
    children: React.ReactNode;
    userId?: number;
};

export function Layout({ children }: LayoutProps) {
    return (
        <div className='layout-container' data-testid='layout-test-id'>
            <Header />
            <div className='main-page-container'>{children}</div>
            <Footer />
        </div>
    );
}
