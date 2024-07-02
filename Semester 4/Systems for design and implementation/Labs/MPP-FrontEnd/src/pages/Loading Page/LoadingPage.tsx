import ReactLoading from 'react-loading';

import './LoadingPage.css';

// #2196F3

export default function LoadingPage() {
    return (
        <div id='main-container' data-testid='main-container'>
            <ReactLoading data-testid='spinner' type='spinningBubbles' color='grey' height={100} width={100} />
        </div>
    );
}
