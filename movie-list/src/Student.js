import {Component} from "react";

// export default class Student extends Component {
//     render() {
//         const {name, marks} = this.props;
//         return (
//             <>
//                 <h1>Hello,{name}</h1>
//                 <h1>You have scored {marks}%</h1>
//                 <hr />
//             </>
//         )
//     }
// }

export default function Student(props) {
    const {name, marks} = props;
    return (
        <>
            <h1>Hello,{name}</h1>
            <h1>You have scored {marks}%</h1>
            <hr />
        </>
    )
}