package tn.healthmonitor.server.model;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.springframework.data.annotation.Id;
import org.springframework.data.annotation.TypeAlias;
import org.springframework.data.mongodb.core.mapping.Document;

@Document("User")
@TypeAlias("User")
@Data
@AllArgsConstructor
@NoArgsConstructor
public class Patient {
    @Id
    String cin ;
    String fullName;
    String age;
    String powerBILinkTemp;
    String powerBILinkBpm;
    String powerBILinkResp;
    public Patient(String cin, String str)
    {
        this.cin = cin ;

    }
    public Patient(String str)
    {
        this("0",str,str,str,str,str);
    }
}
